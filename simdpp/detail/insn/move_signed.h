/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_MOVE_SIGNED_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_MOVE_SIGNED_H

#include <simdpp/types.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/move_r.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class V, int id, bool is_pos>
struct move_l_signed_impl;

template<class V, int id>
struct move_l_signed_impl<V, id, true> {
    static V run(V v) { return move_l<id>(v); }
};

template<class V, int id>
struct move_l_signed_impl<V, id, false> {
    static V run(V v) { return move_r<-id>(v); }
};

/** Equivalent to @c move_l<id> if @a id is positive and to @c move_r<-id> if
    @a id is negative.
*/
template<int id, class V>
V move_l_signed(V a)
{
    return move_l_signed_impl<V, id, (id >= 0)>::run(a);
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp


#endif

