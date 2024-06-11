/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "checks.h"

namespace SIMDPP_ARCH_NAMESPACE {

void main_check_accuracy(const std::string& check_name)
{
    if (check_name == "" || check_name == "log2_approx") {
        check_log2_approx_accuracy();
        check_log2_approx_positive_finite_accuracy();
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE

/* TODO: here we use dispatcher only to register the available functions, not
    to dispatch them. To simplify, use a dummy function for SIMDPP_USER_ARCH_INFO
*/
inline simdpp::Arch get_arch()
{
    return simdpp::Arch();
}

#define SIMDPP_USER_ARCH_INFO get_arch()

SIMDPP_MAKE_DISPATCHER_VOID1(main_check_accuracy, const std::string&)

#if SIMDPP_EMIT_DISPATCHER
std::vector<simdpp::detail::FnVersion> get_run_archs()
{
    simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {};
    using FunPtr = void(*)(const std::string&);
    SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, main_check_accuracy, FunPtr)
    std::vector<simdpp::detail::FnVersion> result;
    result.assign(versions, versions+SIMDPP_DISPATCH_MAX_ARCHS);
    return result;
}
#endif
