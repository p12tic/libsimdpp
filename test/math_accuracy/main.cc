/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "checks.h"
#include "../utils/test_arch.h"
#include "../utils/test_helpers.h"
#include <simdpp/simd.h>

void invoke_check_run_function(const simdpp::detail::FnVersion& fn, const std::string& check_name)
{
    reinterpret_cast<void(*)(const std::string&)>(fn.fun_ptr)(check_name);
}

inline void parse_args(int argc, char* argv[], std::string& name, bool& force_arch)
{
    force_arch = false;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--force_arch") == 0) {
            force_arch = true;
        }
        if (std::strcmp(argv[i], "--force_test") == 0) {
            if (i < argc - 1) {
                name = argv[i + 1];
                i++;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    std::string check_name;
    bool force_arch = false;
    parse_args(argc, argv, check_name, force_arch);

    simdpp::Arch current_arch;
    if (force_arch) {
        current_arch = parse_arch_from_args(argc, argv);
    } else {
        current_arch = get_arch_from_system(false);
    }

    const auto& arch_list = get_run_archs();
    auto null_arch = std::find_if(arch_list.begin(), arch_list.end(), find_arch_null);

    if (null_arch == arch_list.end()) {
        std::cerr << "FATAL: NULL architecture not defined\n";
        return EXIT_FAILURE;
    }

    set_round_to_nearest();

    for (auto it = arch_list.begin(); it != arch_list.end(); it++) {
        if (it->fun_ptr == NULL || it == null_arch) {
            continue;
        }

        if (!simdpp::test_arch_subset(current_arch, it->needed_arch)) {
            std::cerr << "Not testing: " << it->arch_name << std::endl;
            continue;
        }
        std::cerr << "Testing: " << it->arch_name << std::endl;

        invoke_check_run_function(*it, check_name);
    }
}
