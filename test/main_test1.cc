/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "utils/arch_registration.h"
#include "utils/test_results.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

#if __arm__
#include <simdpp/dispatch/get_arch_linux_cpuinfo.h>
#else
#include <simdpp/dispatch/get_arch_raw_cpuid.h>
#endif

/*  We test libsimdpp by comparing the results of the same computations done in
    different 'architectures'. That is, we build a list of results for each
    instruction set available plus the 'null' instruction set (simple,
    non-vectorized code). All tests are generated from the same source code,
    thus any differencies are likely to be caused by bugs in the library.
*/
int main()
{
    std::ostream& err = std::cerr;
    #if __arm__
    simdpp::Arch current_arch = simdpp::get_arch_linux_cpuinfo();
    #else
    simdpp::Arch current_arch = simdpp::get_arch_raw_cpuid();
    #endif
    const auto& arch_list = ArchRegistration::arch_list();
    auto null_arch = std::find_if(arch_list.begin(), arch_list.end(),
                                  [](const ArchRegistration::Arch& a) -> bool
                                  {
                                      return std::strcmp(a.arch, "arch_null") == 0;
                                  });

    if (null_arch == arch_list.end()) {
        std::cerr << "FATAL: NULL architecture not defined\n";
        return EXIT_FAILURE;
    }

    TestResults null_results(null_arch->arch);
    null_arch->run(null_results);

    std::cout << "Num results: " << null_results.num_results() << '\n';

    bool ok = true;

    for (auto it = arch_list.begin(); it != arch_list.end(); it++) {
        if (it == null_arch) {
            continue;
        }

        if (!simdpp::test_arch_subset(current_arch, it->required_arch)) {
            std::cout << "Not testing: " << it->arch << std::endl;
            continue;
        }
        std::cout << "Testing: " << it->arch << std::endl;

        TestResults results(it->arch);
        it->run(results);

        if (!test_equal(null_results, results, err)) {
            ok = false;
        }
    }

    if (!ok) {
        return EXIT_FAILURE;
    }
}
