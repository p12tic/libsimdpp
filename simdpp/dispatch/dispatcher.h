/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_DISPATCHER_H
#define LIBSIMDPP_DISPATCHER_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <atomic>
#include <algorithm>
#include <mutex>
#include <functional>
#include <vector>
#include <simdpp/dispatch/arch.h>

namespace simdpp {

/** @defgroup simd_dispatcher Dispatching support
    @{
*/

using GetArchCb = std::function<Arch()>;

/** @def SIMDPP_USER_ARCH_INFO
    The user must define this macro if he wants to use the dispatcher
    infrastructure. The macro must evaluate to a constant expression that could
    implicitly initialize an object of type @c std::function<Arch()>.

    The macro is used by @c SIMDPP_MAKE_DISPATCHER_* to specify function which
    is invoked to determine which version of the dispatched function to
    dispatch. The macro is just a more convenient method to pass a parameter
    which has high chance to be the same in the majority of use cases. The user
    may redefine the macro and use different definitions for each site of
    @c SIMDPP_MAKE_DISPATCHER_* expansion.

    The function identified by the @c SIMDPP_USER_ARCH_INFO is called at the
    first time the specific dispatcher is invoked. The user must ensure that
    proper synchronization is used if the dispatcher is called concurrently.

    The user must ensure that the returned information is sensible: e.g. SSE2
    must be supported if SSE3 support is indicated.
s
    The @c simdpp/dispatch/get_arch_*.h files provide several ready
    implementations of CPU features detection.
*/

/// @} -- end defgroup

namespace detail {

using VoidFunPtr = void (*)();

struct FnVersion {
    /*  Identifies the instruction support that is needed for this version to
        run.
    */
    Arch needed_arch;

    /*  The type-erased function pointer. Only non-member functions are
        supported.

        We type-erase this pointer to reduce the code bloat by allowing @c
        select_version to be shared across all dispatchers.

        Note, that we can't reinterpret_cast to void*, as that is undefined
        behavior in C++. reinterpret_cast to another function pointer
        type is allowed fortunately.
    */
    VoidFunPtr fun_ptr;
};

inline unsigned select_version_any(std::vector<FnVersion>& versions,
                                   const GetArchCb& get_info_cb)
{
    // No need to try to be very efficient here.
    Arch arch = get_info_cb();
    std::sort(versions.begin(), versions.end(),
              [](const FnVersion& lhs, const FnVersion& rhs) {
                  return lhs.needed_arch > rhs.needed_arch;
              });

    unsigned i;
    for (i = 0; i < versions.size(); ++i) {
        if ((versions[i].needed_arch & ~arch) == Arch::NONE_NULL) {
            break;
        }
    }
    if (i == versions.size()) {
        // The user didn't provide the NONE_NULL version and no SIMD
        // architecture is supported. We can't do anything except to abort
        std::cerr << "simdpp: ERROR: NONE_NULL version not linked into the executable\n";
        std::exit(EXIT_FAILURE);
    }
    return i;
}

#if __GNUC__ && !defined(__clang__)
/*  A workaround for a GCC 4.8 bug: if we don't use threading functions, then
    the threads library is not linked in, the threads implementation is dummy
    and std::call_once throws system_error saying that the operation is not
    supported. If we have a strong reference to at least one function from
    libpthread, everything works
*/
inline void gcc_linker_bug_workaround()
{
    static volatile int i = 0;
    if (i) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnonnull"
        pthread_create(nullptr, nullptr, nullptr, nullptr);
#pragma GCC diagnostic pop
    }
}
#endif

/*  Tracks versions of one particular function. @a Tag must be an unique type
    for each different function. The same @a Tag and @a FunPtr must be used
    when registering versions of the function to be dispatched.
*/
template<class Tag, class FunPtr>
class Dispatcher {
public:

    /** Returns a pointer to the most efficient function for the current
        architecture. This function must not be called before initialization of
        all static objects has finished (i.e. before main() has started).
    */
    static FunPtr get_fun_ptr(const GetArchCb& cb)
    {
#if __GNUC__ && !defined(__clang__)
        gcc_linker_bug_workaround();
#endif
        /*  There are no problems with concurrent initialization, because even
            local static variables are guaranteed to be initialized to zero
            before main() runs.
        */
        static std::atomic<FunPtr> static_fun_ptr{nullptr};

        /*  We can use relaxed memory ordering since there's only single
            transition of the value stored within @a static_fun_ptr. The body
            of the if statement is already protected from data races.
        */
        FunPtr fun_ptr = static_fun_ptr.load(std::memory_order_relaxed);
        if (fun_ptr == nullptr) {
            fun_ptr = reinterpret_cast<FunPtr>(select_version(cb));
            static_fun_ptr.store(fun_ptr, std::memory_order_seq_cst);
        }
        return fun_ptr;
    }

    /** Adds a function to the set of functions to be dispatched. This function
        may only be called from within a constructor of a non-local static
        object.
    */
    static void add_fun_ptr(Arch compile_info, FunPtr fun_ptr)
    {
        FnVersion fn_version;
        fn_version.needed_arch = compile_info;
        fn_version.fun_ptr = reinterpret_cast<VoidFunPtr>(fun_ptr);
        get_all_versions().push_back(fn_version);
    }

private:
    static VoidFunPtr select_version(const GetArchCb& cb)
    {
        /*  This is pretty much the same what we do in @a get_fun_ptr,
            just that we don't use relaxed ordering. This way we incur
            synchronization overhead only on the first call to the dispatched
            function.
        */
        static std::once_flag flag;
        static std::atomic<VoidFunPtr> void_ptr{nullptr};
        std::call_once(flag, select_version_impl, std::ref(void_ptr), cb);
        return void_ptr;
    }

    static void select_version_impl(std::atomic<VoidFunPtr>& fun_ptr,
                                    const GetArchCb& cb)
    {
        auto& v = get_all_versions();
        unsigned id = select_version_any(v, cb);
        fun_ptr = v[id].fun_ptr;
    }

    static std::vector<FnVersion>& get_all_versions()
    {
        static std::vector<FnVersion> versions;
        return versions;
    }
};

/*  Registers a version of a function. @a Tag must be an unique type for each
    function with different name. The same @a Tag and @a FunPtr must be used
    when registering versions of the function to be dispatched.
*/
template<class Tag, class FunPtr>
class DispatchRegistrator {
public:
    DispatchRegistrator(Arch this_compile_info, FunPtr f)
    {
        Dispatcher<Tag,FunPtr>::add_fun_ptr(this_compile_info, f);
    }
};

} // namespace detail
} // namespace simdpp

#include <simdpp/dispatch/macros.h>

#endif
