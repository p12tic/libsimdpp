/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DISPATCH_GET_ARCH_LINUX_CPUINFO_H
#define LIBSIMDPP_DISPATCH_GET_ARCH_LINUX_CPUINFO_H

#if __linux__ && (__arm__ || __i386__ || __amd64__)
#define SIMDPP_HAS_GET_ARCH_LINUX_CPUINFO 1

#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <map>
#include <vector>
#include <simdpp/dispatch/arch.h>

namespace simdpp {

/** @ingroup simdpp_dispatcher
    Retrieves supported architecture from Linux /proc/cpuinfo file.

    Works on X86 and ARM.
*/
inline Arch get_arch_linux_cpuinfo()
{
    Arch res = Arch::NONE_NULL;

    std::map<std::string, Arch> features;
    std::string ident;

#if __arm__
    ident = "Features\t";
    features["neon"] = Arch::ARM_NEON | Arch::ARM_NEON_FLT_SP;

#elif __i386__ || __amd64__
    Arch a_sse2 = Arch::X86_SSE2;
    Arch a_sse3 = a_sse2 | Arch::X86_SSE3;
    Arch a_ssse3 = a_sse3 | Arch::X86_SSSE3;
    Arch a_sse4_1 = a_ssse3 | Arch::X86_SSE4_1;
    Arch a_avx = a_sse4_1 | Arch::X86_AVX;
    Arch a_avx2 = a_avx | Arch::X86_AVX2;
    Arch a_fma3 = a_sse3 | Arch::X86_FMA3;
    Arch a_fma4 = a_sse3 | Arch::X86_FMA4;
    Arch a_xop = a_sse3 | Arch::X86_XOP;

    ident = "flags\t";
    features["sse2"] = a_sse2;
    features["pni"] = a_sse3;
    features["ssse3"] = a_ssse3;
    features["sse4_1"] = a_sse4_1;
    features["avx"] = a_avx;
    features["avx2"] = a_avx2;
    features["fma"] = a_fma3;
    features["fma4"] = a_fma4;
    features["xop"] = a_xop;
#else
    return res;
#endif

    std::ifstream in("/proc/cpuinfo");

    if (!in) {
        return res;
    }

    std::string line;
    while (std::getline(in, line)) {
        // Check whether identification string matches
        if (line.length() < ident.length()) {
            continue;
        }
        std::pair<std::string::iterator,
                  std::string::iterator> r = std::mismatch(ident.begin(), ident.end(), line.begin());
        if (r.first != ident.end()) {
            continue;
        }

        // Get the items
        std::istringstream sin(std::string(&*r.second, &*line.end()));
        std::vector<std::string> items;

        std::copy(std::istream_iterator<std::string>(sin),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(items));

        // Match items to known features
        for (unsigned i = 0; i < items.size(); ++i) {
            const std::string& item = items[i];
            std::map<std::string, Arch>::const_iterator it = features.find(item);
            if (it == features.end()) {
                continue;
            }
            res |= it->second;
        }
    }

    return res;
}

} // namespace simdpp

#endif
#endif
