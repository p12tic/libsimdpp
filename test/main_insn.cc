/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "utils/test_results.h"
#include "utils/test_reporter.h"
#include "insn/tests.h"
#include <simdpp/simd.h>
#include <algorithm>
#include <cfenv>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <vector>

#include <simdpp/dispatch/get_arch_linux_cpuinfo.h>
#include <simdpp/dispatch/get_arch_raw_cpuid.h>
#include <simdpp/dispatch/get_arch_string_list.h>

simdpp::Arch get_arch_from_system(bool is_simulator)
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

simdpp::Arch parse_arch_from_args(int argc, char* argv[])
{
    return simdpp::get_arch_string_list(argv + 1, argc - 1, "--arch_");
}

void parse_args(int argc, char* argv[], bool& is_simulator, bool& force_arch)
{
    is_simulator = false;
    force_arch = false;
    for (int i = 1; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "--simulator") == 0)
            is_simulator = true;
        if (std::strcmp(argv[i], "--force_arch") == 0)
            force_arch = true;
    }
}

bool find_arch_null(const simdpp::detail::FnVersion& a)
{
    return a.arch_name && std::strcmp(a.arch_name, "arch_null") == 0;
}

void invoke_test_run_function(const simdpp::detail::FnVersion& fn,
                              TestResults& res, TestReporter& reporter,
                              const TestOptions& options)
{
    reinterpret_cast<void(*)(TestResults&, TestReporter&, const TestOptions&)>(fn.fun_ptr)(res, reporter, options);
}

/*  We test libsimdpp by comparing the results of the same computations done in
    different 'architectures'. That is, we build a list of results for each
    instruction set available plus the 'null' instruction set (simple,
    non-vectorized code). All tests are generated from the same source code,
    thus any differencies are likely to be caused by bugs in the library.
*/
int main(int argc, char* argv[])
{
    bool is_simulator = false;
    bool force_arch = false;
    parse_args(argc, argv, is_simulator, force_arch);

    simdpp::Arch current_arch;
    if (force_arch)
        current_arch = parse_arch_from_args(argc, argv);
    else
        current_arch = get_arch_from_system(is_simulator);

    TestOptions options;
    options.is_simulator = is_simulator;

    TestReporter tr(std::cerr);

    const auto& arch_list = get_test_archs();
    auto null_arch = std::find_if(arch_list.begin(), arch_list.end(), find_arch_null);

    if (null_arch == arch_list.end()) {
        tr.out() << "FATAL: NULL architecture not defined\n";
        return EXIT_FAILURE;
    }

    set_round_to_nearest();

    TestResults null_results(null_arch->arch_name);
    invoke_test_run_function(*null_arch, null_results, tr, options);

    for (auto it = arch_list.begin(); it != arch_list.end(); it++) {
        if (it->fun_ptr == NULL || it == null_arch) {
            continue;
        }

        if (!simdpp::test_arch_subset(current_arch, it->needed_arch)) {
            tr.out() << "Not testing: " << it->arch_name << std::endl;
            continue;
        }
        tr.out() << "Testing: " << it->arch_name << std::endl;

        TestResults results(it->arch_name);
        invoke_test_run_function(*it, results, tr, options);

        report_test_comparison(null_results, results, tr);
    }

    tr.report_summary();
    return tr.success() ? EXIT_SUCCESS : EXIT_FAILURE;
}
