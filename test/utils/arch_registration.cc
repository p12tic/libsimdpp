/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "arch_registration.h"

ArchRegistration::ArchList& ArchRegistration::arch_list()
{
    static ArchList archs;
    return archs;
}

ArchRegistration::ArchRegistration(TestFunction fn, const char* arch,
                                   simdpp::Arch required_arch)
{
    arch_list().push_back(Arch{fn, arch, required_arch});
}
