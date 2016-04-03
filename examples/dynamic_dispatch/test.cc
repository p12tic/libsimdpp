#include "test.h"
#include <simdpp/simd.h>
#include <iostream>
#include <simdpp/dispatch/get_arch_gcc_builtin_cpu_supports.h>
#include <simdpp/dispatch/get_arch_raw_cpuid.h>
#include <simdpp/dispatch/get_arch_linux_cpuinfo.h>

#if SIMDPP_HAS_GET_ARCH_RAW_CPUID
#define SIMDPP_USER_ARCH_INFO ::simdpp::get_arch_raw_cpuid()
#elif SIMDPP_HAS_GET_ARCH_GCC_BUILTIN_CPU_SUPPORTS
#define SIMDPP_USER_ARCH_INFO ::simdpp::get_arch_gcc_builtin_cpu_supports()
#elif SIMDPP_HAS_GET_ARCH_LINUX_CPUINFO
#define SIMDPP_USER_ARCH_INFO ::simdpp::get_arch_linux_cpuinfo()
#else
#error "Unsupported platform"
#endif

namespace SIMDPP_ARCH_NAMESPACE {

void print_arch()
{
	std::cout << static_cast<unsigned>(simdpp::this_compile_arch()) << '\n';
}

} // namespace SIMDPP_ARCH_NAMESPACE

SIMDPP_MAKE_DISPATCHER_VOID0(print_arch);
