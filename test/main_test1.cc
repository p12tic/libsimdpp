/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#include "arch_registration.h"
#include "test_results.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

/*  We test libsimdpp by comparing the results of the same computations done in
    different 'architectures'. That is, we build a list of results for each
    instruction set available plus the 'null' instruction set (simple,
    non-vectorized code). All tests are generated from the same source code,
    thus any differencies are likely to be caused by bugs in the library.
*/
int main()
{
    std::ostream& err = std::cerr;

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
        std::cout << "Testing: " << it->arch << std::endl;

        if (it == null_arch) {
            continue;
        }

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
