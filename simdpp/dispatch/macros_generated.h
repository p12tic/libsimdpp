/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/


// This file is generated automatically. See tools/gen_dispatcher_macros.py

#ifndef LIBSIMDPP_DISPATCH_MACROS_GENERATED_H
#define LIBSIMDPP_DISPATCH_MACROS_GENERATED_H

#include <simdpp/dispatch/collect_macros_generated.h>

/** @def SIMDPP_MAKE_DISPATCHER_***
    Builds a dispatcher for a specific non-member function. Different macros
    are provided for functions with or without return value and for each
    parameter count.

    Macros in the form @a SIMDPP_MAKE_DISPATCHER_VOID# are to be used for
    functions with no return value. It accepts the following macro parameters:

    * NAME: the unqualified name of the function to dispatch.

    * T1, T2, ..., T#: the types of the parameters of the function that is
      dispatched.

    Macros in the form @a SIMDPP_MAKE_DISPATCHER_RET# are to be used for
    functions that return a value. It accepts the following macro parameters:

    * NAME: the unqualified name of the function to dispatch.

    * R: the type of the return value

    * T1, T2, ..., T#: the types of the parameters of the function that is
      dispatcher.


    @c SIMDPP_ARCH_NAMESPACE::NAME must refer to the function to be disptached
    relative to the namespace in which the @a MAKE_DISPATCHER* macro is used in.
    That is, the macro must be used in a namespace one level up than the
    dispatched function, and that namespace must be @c SIMDPP_ARCH_NAMESPACE

    @a R, T1, T2, ..., T# must be exactly the same as those of the function
    to be dispatched. The dispatched function may be overloaded.

    The macro defines a function with the same signature as the dispatched
    function in the namespace the macro is used. The body of that function
    implements the dispatch mechanism.

    The dispatch functions check the enabled instruction set and select the
    best function on first call. The initialization does not introduce race
    conditions when done concurrently.
*/
/// @{
#if SIMDPP_EMIT_DISPATCHER


#define SIMDPP_MAKE_DISPATCHER_VOID0(NAME)                                    \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, void(*)())                            \
                                                                              \
void NAME()                                                                   \
{                                                                             \
    typedef void(*FunPtr)();                                                  \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
     selected();                                                              \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)())                     \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID1(NAME,T1)                                 \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, void(*)(T1))                          \
                                                                              \
void NAME(T1 a1)                                                              \
{                                                                             \
    typedef void(*FunPtr)(T1);                                                \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
     selected(a1);                                                            \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1))                   \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID2(NAME,T1,T2)                              \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, void(*)(T1,T2))                       \
                                                                              \
void NAME(T1 a1,T2 a2)                                                        \
{                                                                             \
    typedef void(*FunPtr)(T1,T2);                                             \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
     selected(a1,a2);                                                         \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2))                \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID3(NAME,T1,T2,T3)                           \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, void(*)(T1,T2,T3))                    \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3)                                                  \
{                                                                             \
    typedef void(*FunPtr)(T1,T2,T3);                                          \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
     selected(a1,a2,a3);                                                      \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3))             \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID4(NAME,T1,T2,T3,T4)                        \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, void(*)(T1,T2,T3,T4))                 \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4)                                            \
{                                                                             \
    typedef void(*FunPtr)(T1,T2,T3,T4);                                       \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
     selected(a1,a2,a3,a4);                                                   \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4))          \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID5(NAME,T1,T2,T3,T4,T5)                     \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, void(*)(T1,T2,T3,T4,T5))              \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5)                                      \
{                                                                             \
    typedef void(*FunPtr)(T1,T2,T3,T4,T5);                                    \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
     selected(a1,a2,a3,a4,a5);                                                \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4,T5))       \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID6(NAME,T1,T2,T3,T4,T5,T6)                  \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, void(*)(T1,T2,T3,T4,T5,T6))           \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6)                                \
{                                                                             \
    typedef void(*FunPtr)(T1,T2,T3,T4,T5,T6);                                 \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
     selected(a1,a2,a3,a4,a5,a6);                                             \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4,T5,T6))    \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID7(NAME,T1,T2,T3,T4,T5,T6,T7)               \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, void(*)(T1,T2,T3,T4,T5,T6,T7))        \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7)                          \
{                                                                             \
    typedef void(*FunPtr)(T1,T2,T3,T4,T5,T6,T7);                              \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
     selected(a1,a2,a3,a4,a5,a6,a7);                                          \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4,T5,T6,T7)) \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID8(NAME,T1,T2,T3,T4,T5,T6,T7,T8)            \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, void(*)(T1,T2,T3,T4,T5,T6,T7,T8))     \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8)                    \
{                                                                             \
    typedef void(*FunPtr)(T1,T2,T3,T4,T5,T6,T7,T8);                           \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
     selected(a1,a2,a3,a4,a5,a6,a7,a8);                                       \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4,T5,T6,T7,T8))\
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID9(NAME,T1,T2,T3,T4,T5,T6,T7,T8,T9)         \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, void(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9))  \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9)              \
{                                                                             \
    typedef void(*FunPtr)(T1,T2,T3,T4,T5,T6,T7,T8,T9);                        \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
     selected(a1,a2,a3,a4,a5,a6,a7,a8,a9);                                    \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9))\
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET0(NAME,R)                                   \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, R(*)())                               \
                                                                              \
R NAME()                                                                      \
{                                                                             \
    typedef R(*FunPtr)();                                                     \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
    return selected();                                                        \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)())                        \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET1(NAME,R,T1)                                \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, R(*)(T1))                             \
                                                                              \
R NAME(T1 a1)                                                                 \
{                                                                             \
    typedef R(*FunPtr)(T1);                                                   \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
    return selected(a1);                                                      \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1))                      \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET2(NAME,R,T1,T2)                             \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, R(*)(T1,T2))                          \
                                                                              \
R NAME(T1 a1,T2 a2)                                                           \
{                                                                             \
    typedef R(*FunPtr)(T1,T2);                                                \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
    return selected(a1,a2);                                                   \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2))                   \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET3(NAME,R,T1,T2,T3)                          \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, R(*)(T1,T2,T3))                       \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3)                                                     \
{                                                                             \
    typedef R(*FunPtr)(T1,T2,T3);                                             \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
    return selected(a1,a2,a3);                                                \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3))                \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET4(NAME,R,T1,T2,T3,T4)                       \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, R(*)(T1,T2,T3,T4))                    \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4)                                               \
{                                                                             \
    typedef R(*FunPtr)(T1,T2,T3,T4);                                          \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
    return selected(a1,a2,a3,a4);                                             \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4))             \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET5(NAME,R,T1,T2,T3,T4,T5)                    \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, R(*)(T1,T2,T3,T4,T5))                 \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5)                                         \
{                                                                             \
    typedef R(*FunPtr)(T1,T2,T3,T4,T5);                                       \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
    return selected(a1,a2,a3,a4,a5);                                          \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4,T5))          \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET6(NAME,R,T1,T2,T3,T4,T5,T6)                 \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, R(*)(T1,T2,T3,T4,T5,T6))              \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6)                                   \
{                                                                             \
    typedef R(*FunPtr)(T1,T2,T3,T4,T5,T6);                                    \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
    return selected(a1,a2,a3,a4,a5,a6);                                       \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4,T5,T6))       \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET7(NAME,R,T1,T2,T3,T4,T5,T6,T7)              \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, R(*)(T1,T2,T3,T4,T5,T6,T7))           \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7)                             \
{                                                                             \
    typedef R(*FunPtr)(T1,T2,T3,T4,T5,T6,T7);                                 \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
    return selected(a1,a2,a3,a4,a5,a6,a7);                                    \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4,T5,T6,T7))    \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET8(NAME,R,T1,T2,T3,T4,T5,T6,T7,T8)           \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, R(*)(T1,T2,T3,T4,T5,T6,T7,T8))        \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8)                       \
{                                                                             \
    typedef R(*FunPtr)(T1,T2,T3,T4,T5,T6,T7,T8);                              \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
    return selected(a1,a2,a3,a4,a5,a6,a7,a8);                                 \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4,T5,T6,T7,T8)) \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET9(NAME,R,T1,T2,T3,T4,T5,T6,T7,T8,T9)        \
                                                                              \
SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME, R(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9))     \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9)                 \
{                                                                             \
    typedef R(*FunPtr)(T1,T2,T3,T4,T5,T6,T7,T8,T9);                           \
    static FunPtr selected = NULL;                                            \
    if (selected == NULL) {                                                   \
        ::simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {}; \
        SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, NAME, FunPtr)             \
        ::simdpp::detail::FnVersion version =                                 \
            ::simdpp::detail::select_version_any(versions,                    \
                SIMDPP_DISPATCH_MAX_ARCHS, SIMDPP_USER_ARCH_INFO);            \
        selected = reinterpret_cast<FunPtr>(version.fun_ptr);                 \
    }                                                                         \
    return selected(a1,a2,a3,a4,a5,a6,a7,a8,a9);                              \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9))\
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#else


#define SIMDPP_MAKE_DISPATCHER_VOID0(NAME)                                    \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)())                     \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID1(NAME,T1)                                 \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1))                   \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID2(NAME,T1,T2)                              \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2))                \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID3(NAME,T1,T2,T3)                           \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3))             \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID4(NAME,T1,T2,T3,T4)                        \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4))          \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID5(NAME,T1,T2,T3,T4,T5)                     \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4,T5))       \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID6(NAME,T1,T2,T3,T4,T5,T6)                  \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4,T5,T6))    \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID7(NAME,T1,T2,T3,T4,T5,T6,T7)               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4,T5,T6,T7)) \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID8(NAME,T1,T2,T3,T4,T5,T6,T7,T8)            \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4,T5,T6,T7,T8))\
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_VOID9(NAME,T1,T2,T3,T4,T5,T6,T7,T8,T9)         \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(void(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9))\
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET0(NAME,R)                                   \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)())                        \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET1(NAME,R,T1)                                \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1))                      \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET2(NAME,R,T1,T2)                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2))                   \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET3(NAME,R,T1,T2,T3)                          \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3))                \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET4(NAME,R,T1,T2,T3,T4)                       \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4))             \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET5(NAME,R,T1,T2,T3,T4,T5)                    \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4,T5))          \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET6(NAME,R,T1,T2,T3,T4,T5,T6)                 \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4,T5,T6))       \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET7(NAME,R,T1,T2,T3,T4,T5,T6,T7)              \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4,T5,T6,T7))    \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET8(NAME,R,T1,T2,T3,T4,T5,T6,T7,T8)           \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4,T5,T6,T7,T8)) \
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#define SIMDPP_MAKE_DISPATCHER_RET9(NAME,R,T1,T2,T3,T4,T5,T6,T7,T8,T9)        \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
::simdpp::detail::FnVersion register_fn_##NAME(R(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9))\
{                                                                             \
    ::simdpp::detail::FnVersion ret;                                          \
    ret.fun_ptr = reinterpret_cast<void (*)()>(&NAME);                        \
    ret.needed_arch = ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch();   \
    ret.arch_name = SIMDPP_ARCH_NAME;                                         \
    return ret;                                                               \
}                                                                             \
} /* namespace SIMDPP_ARCH_NAMESPACE */                                       \

#endif
/// @}

#endif

