/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_ARCH_REGISTRATION_H
#define LIBSIMDPP_TEST_ARCH_REGISTRATION_H

#include "test_results.h"
#include <functional>
#include <vector>
#include <utility>

class ArchRegistration {
public:

    using TestFunction = std::function<void(TestResults&)>;

    struct Arch {
        TestFunction run;
        const char* arch;
    };
    using ArchList = std::vector<Arch>;

    ArchRegistration(TestFunction fn, const char* arch)
    {
        arch_list().push_back(Arch{fn, arch});
    }

    static ArchList& arch_list();
};

#endif

