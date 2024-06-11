/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include <simdpp/dispatch/get_arch_linux_cpuinfo.h>
#include <simdpp/dispatch/get_arch_raw_cpuid.h>
#include <simdpp/dispatch/get_arch_string_list.h>

inline simdpp::Arch get_arch_from_system(bool is_simulator)
{
    (void) is_simulator;
    std::vector<simdpp::Arch> supported_archs;
#if SIMDPP_HAS_GET_ARCH_LINUX_CPUINFO
    if (!is_simulator)
        supported_archs.push_back(simdpp::get_arch_linux_cpuinfo());
#endif
#if SIMDPP_HAS_GET_ARCH_RAW_CPUID
    supported_archs.push_back(simdpp::get_arch_raw_cpuid());
#endif
    if (supported_archs.empty()) {
        std::cerr << "No architecture information could be retrieved. Testing not supported\n";
        std::exit(EXIT_FAILURE);
    }

    simdpp::Arch result = supported_archs.front();
    for (unsigned i = 1; i < supported_archs.size(); ++i) {
        if (supported_archs[i] != result) {
            std::cerr << "Different CPU architecture evaluators return different results\n"
                      << std::hex << (unsigned)result << " " << i << " "
                      << std::hex << (unsigned)supported_archs[i] << "\n";
            std::exit(EXIT_FAILURE);
        }
    }
    std::cerr << "Evaluated architecture bit set: " << std::hex
              << (unsigned) result << "\n" << std::dec;
    return result;
}

inline simdpp::Arch parse_arch_from_args(int argc, char* argv[])
{
    return simdpp::get_arch_string_list(argv + 1, argc - 1, "--arch_");
}

inline bool find_arch_null(const simdpp::detail::FnVersion& a)
{
    return a.arch_name && std::strcmp(a.arch_name, "arch_null") == 0;
}
