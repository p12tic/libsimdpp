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

#include <functional>
#include <simdpp/arch.h>

namespace simdpp {

/** @defgroup simd_dispatcher Dispatching support
    @{
*/

using GetArchCb = std::function<ArchUserInfo()>;

/** @macro SIMDPP_USER_ARCH_INFO
    User-definable macro that specifies user-defined way to get supported
    instruction sets of the current processor. If the macro is defined, this
    must be done before including simdpp/simd.h. The macro must evaluate to
    a constant expression that could implicitly initialize an object of type
    @c std::function<ArchUserInfo()>.

    The return value @a x (of type @c ArchUserInfo) is interpreted as follows:

    x.supported identifies features that are supported by the processor.
    x.unsupported identifies features that are not supported by the processor.

    If some features are defined as neither supported or not supported
    (any flags not set in the result of x.supported | x.unsupported), then the
    internal libsimdpp implementation is used to determine whether the current
    processor supports them or not.

    To override the internal libsimdpp implementation completely, set
    x.unsupported = ~x.supported.

    The user must ensure that the returned information is sensible: e.g. SSE2
    must be supported if SSE3 support is indicated.
*/
#ifndef SIMDPP_USER_ARCH_INFO
#define SIMDPP_USER_ARCH_INFO ::simdpp::detail::default_user_get_arch_info
#endif

/// @} -- end defgroup

} // namespace simdpp

#include <simdpp/detail/dispatcher.h>
#include <simdpp/dispatcher_macros.h>

#endif
