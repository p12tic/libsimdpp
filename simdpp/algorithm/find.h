/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_FIND_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_FIND_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <algorithm>//find
#include <simdpp/types/traits.h>
#include <simdpp/detail/insn/load.h>
#include <simdpp/algorithm/helper_input_range.h>

namespace simdpp {
    namespace SIMDPP_ARCH_NAMESPACE {

        template<typename T, typename U>
        T const* find(T const* first, T const* last, U val)
        {
            struct UnaryPredicateEqualValue
            {
            public:
                UnaryPredicateEqualValue(T val) :m_val(val), m_val_simd(splat(val)) {}
                using simd_mask_T = typename typetraits<T>::simd_mask_type;
                using simd_type_T = typename typetraits<T>::simd_type;

                bool                  operator()(T a)           const { return a == m_val; }
                simd_mask_T operator()(const simd_type_T& a) const { return cmp_eq(a, m_val_simd); }
            private:
                T m_val;
                simd_type_T m_val_simd;
            };

#ifndef NDEBUG //precondition debug mode           
            if (!first)
                throw std::runtime_error("find - null ptr first.");
            if (!last)
                throw std::runtime_error("find - null ptr last.");
#endif
            using simd_type_T = typename typetraits<T>::simd_type;
            using simd_mask_T =typename typetraits<T>::simd_mask_type;

            if (first == last) return last;

            //define loopcounter
            const auto simd_size = simd_type_T::base_length;
            const auto size = std::distance(first, last);
            //note enforce that input is aligned when we start the main simd loop
            const auto range = helper_input_range(first, last);
            const auto size_prologue_loop = range.first;
            const auto size_simd_loop = range.second;

            //prologue
            auto lastprologue = first + size_prologue_loop;
            const auto resprologue = std::find(first, lastprologue, val);
            if (resprologue != lastprologue) return resprologue;

            //simd loop
            auto i = size_prologue_loop;

            //workaraund not test_bits_any for mask type
            const simd_type_T on = splat(T(1));
            const simd_type_T off = splat(T(0));
            const auto pred = UnaryPredicateEqualValue(val);
            for (; i < size_simd_loop; i += simd_size)
            {
                //TR why can't test_bits_any not available for mask?
                const simd_mask_T mask=pred(load(lastprologue));
                const auto res = blend(on, off,mask);
                if (test_bits_any(res)) //match extract exact position
                {
                    return std::find_if(lastprologue, lastprologue + simd_size, pred); //or extract position from res ?
                }
                lastprologue += simd_size;
            }

            //epilogue
            return std::find(lastprologue, last, val);
        }

    } // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp
#endif //LIBSIMDPP_SIMDPP_ALGORITHM_FIND_H
