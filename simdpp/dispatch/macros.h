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

// This file is generated automatically. See tools/gen_dispatcher_macros.py

#ifndef LIBSIMDPP_DISPATCH_MACROS_H
#define LIBSIMDPP_DISPATCH_MACROS_H

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
    implements the dispatch mechanism. The function must not be called before
    main() starts.
*/
/// @{
#ifdef SIMDPP_USE_NULL


#define SIMDPP_MAKE_DISPATCHER_VOID0(NAME)                                    \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
void NAME()                                                                   \
{                                                                             \
    using FunPtr = void(*)();                                                 \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
     ::simdpp::detail::Dispatcher<                                            \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)();                                  \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)()                                     \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)()>(&NAME));                                       \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID1(NAME,T1)                                 \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
void NAME(T1 a1)                                                              \
{                                                                             \
    using FunPtr = void(*)(T1);                                               \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
     ::simdpp::detail::Dispatcher<                                            \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1);                                \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1)                                   \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1)>(&NAME));                                     \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID2(NAME,T1,T2)                              \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
void NAME(T1 a1,T2 a2)                                                        \
{                                                                             \
    using FunPtr = void(*)(T1,T2);                                            \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
     ::simdpp::detail::Dispatcher<                                            \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2);                             \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2)                                \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2)>(&NAME));                                  \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID3(NAME,T1,T2,T3)                           \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3)                                                  \
{                                                                             \
    using FunPtr = void(*)(T1,T2,T3);                                         \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
     ::simdpp::detail::Dispatcher<                                            \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3);                          \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3)                             \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3)>(&NAME));                               \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID4(NAME,T1,T2,T3,T4)                        \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4)                                            \
{                                                                             \
    using FunPtr = void(*)(T1,T2,T3,T4);                                      \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
     ::simdpp::detail::Dispatcher<                                            \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4);                       \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4)                          \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4)>(&NAME));                            \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID5(NAME,T1,T2,T3,T4,T5)                     \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5)                                      \
{                                                                             \
    using FunPtr = void(*)(T1,T2,T3,T4,T5);                                   \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
     ::simdpp::detail::Dispatcher<                                            \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4,a5);                    \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4,T5)                       \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4,T5)>(&NAME));                         \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID6(NAME,T1,T2,T3,T4,T5,T6)                  \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6)                                \
{                                                                             \
    using FunPtr = void(*)(T1,T2,T3,T4,T5,T6);                                \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
     ::simdpp::detail::Dispatcher<                                            \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4,a5,a6);                 \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4,T5,T6)                    \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4,T5,T6)>(&NAME));                      \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID7(NAME,T1,T2,T3,T4,T5,T6,T7)               \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7)                          \
{                                                                             \
    using FunPtr = void(*)(T1,T2,T3,T4,T5,T6,T7);                             \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
     ::simdpp::detail::Dispatcher<                                            \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4,a5,a6,a7);              \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4,T5,T6,T7)                 \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4,T5,T6,T7)>(&NAME));                   \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID8(NAME,T1,T2,T3,T4,T5,T6,T7,T8)            \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8)                    \
{                                                                             \
    using FunPtr = void(*)(T1,T2,T3,T4,T5,T6,T7,T8);                          \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
     ::simdpp::detail::Dispatcher<                                            \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4,a5,a6,a7,a8);           \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4,T5,T6,T7,T8)              \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4,T5,T6,T7,T8)>(&NAME));                \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID9(NAME,T1,T2,T3,T4,T5,T6,T7,T8,T9)         \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
void NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9)              \
{                                                                             \
    using FunPtr = void(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9);                       \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
     ::simdpp::detail::Dispatcher<                                            \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4,a5,a6,a7,a8,a9);        \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9)           \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9)>(&NAME));             \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET0(NAME,R)                                   \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
R NAME()                                                                      \
{                                                                             \
    using FunPtr = R(*)();                                                    \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
    return ::simdpp::detail::Dispatcher<                                      \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)();                                  \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)()                                        \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)()>(&NAME));                                          \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET1(NAME,R,T1)                                \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
R NAME(T1 a1)                                                                 \
{                                                                             \
    using FunPtr = R(*)(T1);                                                  \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
    return ::simdpp::detail::Dispatcher<                                      \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1);                                \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1)                                      \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1)>(&NAME));                                        \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET2(NAME,R,T1,T2)                             \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
R NAME(T1 a1,T2 a2)                                                           \
{                                                                             \
    using FunPtr = R(*)(T1,T2);                                               \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
    return ::simdpp::detail::Dispatcher<                                      \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2);                             \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2)                                   \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2)>(&NAME));                                     \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET3(NAME,R,T1,T2,T3)                          \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3)                                                     \
{                                                                             \
    using FunPtr = R(*)(T1,T2,T3);                                            \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
    return ::simdpp::detail::Dispatcher<                                      \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3);                          \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3)                                \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3)>(&NAME));                                  \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET4(NAME,R,T1,T2,T3,T4)                       \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4)                                               \
{                                                                             \
    using FunPtr = R(*)(T1,T2,T3,T4);                                         \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
    return ::simdpp::detail::Dispatcher<                                      \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4);                       \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4)                             \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4)>(&NAME));                               \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET5(NAME,R,T1,T2,T3,T4,T5)                    \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5)                                         \
{                                                                             \
    using FunPtr = R(*)(T1,T2,T3,T4,T5);                                      \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
    return ::simdpp::detail::Dispatcher<                                      \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4,a5);                    \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4,T5)                          \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4,T5)>(&NAME));                            \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET6(NAME,R,T1,T2,T3,T4,T5,T6)                 \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6)                                   \
{                                                                             \
    using FunPtr = R(*)(T1,T2,T3,T4,T5,T6);                                   \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
    return ::simdpp::detail::Dispatcher<                                      \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4,a5,a6);                 \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4,T5,T6)                       \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4,T5,T6)>(&NAME));                         \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET7(NAME,R,T1,T2,T3,T4,T5,T6,T7)              \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7)                             \
{                                                                             \
    using FunPtr = R(*)(T1,T2,T3,T4,T5,T6,T7);                                \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
    return ::simdpp::detail::Dispatcher<                                      \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4,a5,a6,a7);              \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4,T5,T6,T7)                    \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4,T5,T6,T7)>(&NAME));                      \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET8(NAME,R,T1,T2,T3,T4,T5,T6,T7,T8)           \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8)                       \
{                                                                             \
    using FunPtr = R(*)(T1,T2,T3,T4,T5,T6,T7,T8);                             \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
    return ::simdpp::detail::Dispatcher<                                      \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4,a5,a6,a7,a8);           \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4,T5,T6,T7,T8)                 \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4,T5,T6,T7,T8)>(&NAME));                   \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET9(NAME,R,T1,T2,T3,T4,T5,T6,T7,T8,T9)        \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
R NAME(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9)                 \
{                                                                             \
    using FunPtr = R(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9);                          \
    using Tag = simdpp_ ## NAME ## _tag;                                      \
    return ::simdpp::detail::Dispatcher<                                      \
        Tag,FunPtr                                                            \
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)(a1,a2,a3,a4,a5,a6,a7,a8,a9);        \
}                                                                             \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9)              \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9)>(&NAME));                \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#else


#define SIMDPP_MAKE_DISPATCHER_VOID0(NAME)                                    \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)()                                     \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)()>(&NAME));                                       \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID1(NAME,T1)                                 \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1)                                   \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1)>(&NAME));                                     \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID2(NAME,T1,T2)                              \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2)                                \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2)>(&NAME));                                  \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID3(NAME,T1,T2,T3)                           \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3)                             \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3)>(&NAME));                               \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID4(NAME,T1,T2,T3,T4)                        \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4)                          \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4)>(&NAME));                            \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID5(NAME,T1,T2,T3,T4,T5)                     \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4,T5)                       \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4,T5)>(&NAME));                         \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID6(NAME,T1,T2,T3,T4,T5,T6)                  \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4,T5,T6)                    \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4,T5,T6)>(&NAME));                      \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID7(NAME,T1,T2,T3,T4,T5,T6,T7)               \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4,T5,T6,T7)                 \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4,T5,T6,T7)>(&NAME));                   \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID8(NAME,T1,T2,T3,T4,T5,T6,T7,T8)            \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4,T5,T6,T7,T8)              \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4,T5,T6,T7,T8)>(&NAME));                \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_VOID9(NAME,T1,T2,T3,T4,T5,T6,T7,T8,T9)         \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,void(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9)           \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<void(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9)>(&NAME));             \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET0(NAME,R)                                   \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)()                                        \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)()>(&NAME));                                          \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET1(NAME,R,T1)                                \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1)                                      \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1)>(&NAME));                                        \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET2(NAME,R,T1,T2)                             \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2)                                   \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2)>(&NAME));                                     \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET3(NAME,R,T1,T2,T3)                          \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3)                                \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3)>(&NAME));                                  \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET4(NAME,R,T1,T2,T3,T4)                       \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4)                             \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4)>(&NAME));                               \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET5(NAME,R,T1,T2,T3,T4,T5)                    \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4,T5)                          \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4,T5)>(&NAME));                            \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET6(NAME,R,T1,T2,T3,T4,T5,T6)                 \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4,T5,T6)                       \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4,T5,T6)>(&NAME));                         \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET7(NAME,R,T1,T2,T3,T4,T5,T6,T7)              \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4,T5,T6,T7)                    \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4,T5,T6,T7)>(&NAME));                      \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET8(NAME,R,T1,T2,T3,T4,T5,T6,T7,T8)           \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4,T5,T6,T7,T8)                 \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4,T5,T6,T7,T8)>(&NAME));                   \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#define SIMDPP_MAKE_DISPATCHER_RET9(NAME,R,T1,T2,T3,T4,T5,T6,T7,T8,T9)        \
struct simdpp_ ## NAME ## _tag;                                               \
                                                                              \
namespace SIMDPP_ARCH_NAMESPACE {                                             \
                                                                              \
static ::simdpp::detail::DispatchRegistrator<                                 \
        simdpp_ ## NAME ## _tag,R(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9)              \
> simdpp_dispatch_registrator_ ## NAME (                                      \
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),                 \
        static_cast<R(*)(T1,T2,T3,T4,T5,T6,T7,T8,T9)>(&NAME));                \
                                                                              \
} /* namespace SIMDPP_ARCH_NAMESPACE */


#endif
/// @}

#endif

