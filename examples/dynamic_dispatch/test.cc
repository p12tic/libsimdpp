#include "test.h"
#include <simdpp/simd.h>
#include <iostream>
#include <simdpp/dispatch/get_arch_gcc_builtin_cpu_supports.h>
#define SIMDPP_USER_ARCH_INFO ::simdpp::get_arch_gcc_builtin_cpu_supports

namespace SIMDPP_ARCH_NAMESPACE {

void print_arch()
{
	std::cout << static_cast<unsigned>(simdpp::this_compile_arch()) << '\n';
}

} // namespace SIMDPP_ARCH_NAMESPACE

SIMDPP_MAKE_DISPATCHER_VOID0(print_arch);
