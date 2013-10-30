/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <string>

struct UnaryTag {};
struct BinaryTag {};

enum {
    WORKAREA_SIZE = 1024
};

alignas(32) char work_area[WORKAREA_SIZE*32];

using namespace simdpp;

// The following functions attempt to perform an operation on a and b such that
// the compiler is unable to perform any optimizations
inline basic_int8x16 isolate(basic_int8x16 a, basic_int8x16 b)
{
    return avg((uint16x8)a, (uint16x8)b);
}

inline basic_int16x8 isolate(basic_int16x8 a, basic_int16x8 b)
{
    return avg((uint16x8)a, (uint16x8)b);
}

inline basic_int32x4 isolate(basic_int32x4 a, basic_int32x4 b)
{
    return avg((uint16x8)a, (uint16x8)b);
}

inline basic_int64x2 isolate(basic_int64x2 a, basic_int64x2 b)
{
    return avg((uint16x8)a, (uint16x8)b);
}

inline float32x4 isolate(float32x4 a, float32x4 b)
{
    return mul(a, b);
}

/* Benchmarking instruction performance without highel level abstractions is
    painful. One must ensure that the measurement loop is quite expensive by
    itself, otherwise we're measuring the bandwidth of the caches (e.g. on
    Cortex-9 and older ARMs the total load/save bandwidth is only 64
    bits/cycle). On top of that we must ensure that the compiler doesn't
    optimize anything out
*/
template<class V, class F>
inline V perf_one_iteration(UnaryTag, V v1, V v2, V c1, V c2, F f)
{
    V v3 = bit_xor(v1, v2);

    V a1 = bit_cast<V>(isolate(v1, c1));
    V a2 = bit_cast<V>(isolate(v1, c2));
    V a3 = bit_cast<V>(isolate(v2, c1));
    V a4 = bit_cast<V>(isolate(v2, c2));
    V a5 = bit_cast<V>(isolate(v1, v3));
    V a6 = bit_cast<V>(isolate(v2, v3));

    V b1 = bit_cast<V>(f(a1));
    V b2 = bit_cast<V>(f(a2));
    V b3 = bit_cast<V>(f(a3));
    V b4 = bit_cast<V>(f(a4));
    V b5 = bit_cast<V>(f(a5));
    V b6 = bit_cast<V>(f(a6));

    a1 = bit_cast<V>(isolate(b1, v2));
    a2 = bit_cast<V>(isolate(b2, c1));
    a3 = bit_cast<V>(isolate(b3, c2));
    a4 = bit_cast<V>(isolate(b4, v1));
    a5 = bit_cast<V>(isolate(b5, v2));
    a6 = bit_cast<V>(isolate(b6, v1));

    a1 = bit_cast<V>(bit_xor(a1, a2));
    a3 = bit_cast<V>(bit_xor(a3, a4));
    a5 = bit_cast<V>(bit_xor(a5, a6));
    a1 = bit_cast<V>(bit_or(a1, a3));
    a1 = bit_cast<V>(bit_or(a1, a5));
    return a1;
}

template<class V, class F>
inline V perf_one_iteration(BinaryTag, V v1, V v2, V c1, V c2, F f)
{
    V v3 = bit_xor(v1, v2);

    V a1 = bit_cast<V>(isolate(v1, c1));
    V a2 = bit_cast<V>(isolate(v1, c2));
    V a3 = bit_cast<V>(isolate(v2, c1));
    V a4 = bit_cast<V>(isolate(v2, c2));
    V a5 = bit_cast<V>(isolate(v1, v3));
    V a6 = bit_cast<V>(isolate(v2, v3));

    V b1 = bit_cast<V>(f(a1, c2));
    V b2 = bit_cast<V>(f(a2, v2));
    V b3 = bit_cast<V>(f(a3, v2));
    V b4 = bit_cast<V>(f(a4, c1));
    V b5 = bit_cast<V>(f(a5, c2));
    V b6 = bit_cast<V>(f(a6, c1));

    a1 = bit_cast<V>(isolate(b1, v2));
    a2 = bit_cast<V>(isolate(b2, c1));
    a3 = bit_cast<V>(isolate(b3, c2));
    a4 = bit_cast<V>(isolate(b4, v1));
    a5 = bit_cast<V>(isolate(b5, v2));
    a6 = bit_cast<V>(isolate(b6, v1));

    a1 = bit_cast<V>(bit_xor(a1, a2));
    a3 = bit_cast<V>(bit_xor(a3, a4));
    a5 = bit_cast<V>(bit_xor(a5, a6));
    a1 = bit_cast<V>(bit_or(a1, a3));
    a1 = bit_cast<V>(bit_or(a1, a5));
    return a1;
}

/// Applies @a f @a count*6 times.
template<class V, class Tag, class F>
inline void perf_cycle(Tag, unsigned count, F f)
{
    typedef typename V::element_type E;
    const unsigned length = V::length;

    unsigned z = 0;

    // count is much larger than workarea_size
    for (unsigned i = 0; i < count / WORKAREA_SIZE; i++) {
        E* src;
        E* dst;
        src = dst = reinterpret_cast<E*>(work_area);

        V c1, c2;
        load(c1, src+length*z++);
        load(c2, src+length*z++);

        z = z % (WORKAREA_SIZE - 2);
        for (unsigned j = 0; j < WORKAREA_SIZE; j++) {
            V v1, v2;
            load(v1, src);
            load(v2, src + length);
            v1 = perf_one_iteration(Tag(), v1, v2, c1, c2, f);
            store(dst, v1);
            src+= length*2;
            dst+= length*2;
        }
    }
}

template<class V>
inline int get_baseline(UnaryTag, unsigned mhz, unsigned ms)
{
    std::clock_t c_begin = std::clock();
    for (unsigned i = 0; i < mhz; i++) {
        perf_cycle<V>(UnaryTag(), 1000*ms, [](V a) { return a; });
    }
    std::clock_t c_end = std::clock();

    return c_end - c_begin;
}

template<class V>
inline int get_baseline(BinaryTag, unsigned mhz, unsigned ms)
{
    std::clock_t c_begin = std::clock();
    for (unsigned i = 0; i < mhz; i++) {
        perf_cycle<V>(BinaryTag(), 1000*ms, [](V a, V) { return a; });
    }
    std::clock_t c_end = std::clock();

    return c_end - c_begin;
}
/** Measures the performance of function f. The results are printed to the
    standard output.

    @param mhz The speed of the processor in MHz
    @param ms A coefficient determining the duration of the test. The actual
        duration is a multiple of @a ms milliseconds
    @param id An identification string to print.
    @param f A function object that returns a value of type V if called with
        two parameters of type V.
*/
template<class V, class Tag, class F>
inline void measure_func(Tag, unsigned mhz, unsigned ms, const char* id, F f)
{
    // unforutunately we must run this for each measurement
    int baseline = get_baseline<V>(Tag(), mhz, ms);

    std::clock_t c_begin = std::clock();
    for (unsigned i = 0; i < mhz; i++) {
        perf_cycle<V>(Tag(), 1000*ms, f);
    }
    std::clock_t c_end = std::clock();

    int diff0 = c_end - c_begin;
    int diff = diff0 - baseline;

    float res0 = (1000.0 / ms) * (float(diff0) / (CLOCKS_PER_SEC));
    float res = (1000.0 / ms) * (float(diff) / (CLOCKS_PER_SEC));
    if (res < 0) {
        res = 0.0;
    }
    res /= 6;   // 6 operations per iteration
    res0 /= 6;
    std::cout << std::setw(30) << id << ':'
              << std::setw(10) << res << " clock/ops   ( "
              << res0 << " clock/ops total) " << std::endl;

}

// 64-bit floating point operations are not yet supported

#define TEST_PERF_T1(mhz, ms, V, F)                               \
    measure_func<V>(UnaryTag(), mhz, ms, #F "/" #V, [](V a) { return F(a); });

#define TEST_PERF_T2(mhz, ms, V, F)                               \
    measure_func<V>(BinaryTag(), mhz, ms, #F "/" #V, [](V a, V b) { return F(a,b); });

#define TEST_PERF_NO_I64_T1(mhz, ms, F)                           \
    TEST_PERF_T1(mhz, ms, int8x16, F)                             \
    TEST_PERF_T1(mhz, ms, int16x8, F)                             \
    TEST_PERF_T1(mhz, ms, int32x4, F)                             \
    TEST_PERF_T1(mhz, ms, float32x4, F)                           \
//    TEST_PERF_T1(mhz, ms, float64x2, F)

#define TEST_PERF_ALL_T1(mhz, ms, F)                              \
    TEST_PERF_T1(mhz, ms, int8x16, F)                             \
    TEST_PERF_T1(mhz, ms, int16x8, F)                             \
    TEST_PERF_T1(mhz, ms, int32x4, F)                             \
    TEST_PERF_T1(mhz, ms, int64x2, F)                             \
    TEST_PERF_T1(mhz, ms, float32x4, F)                           \
 //   TEST_PERF_T1(mhz, ms, float64x2, F)

#define TEST_PERF_NO_I64_T2(mhz, ms, F)                           \
    TEST_PERF_T2(mhz, ms, int8x16, F)                             \
    TEST_PERF_T2(mhz, ms, int16x8, F)                             \
    TEST_PERF_T2(mhz, ms, int32x4, F)                             \
    TEST_PERF_T2(mhz, ms, float32x4, F)                           \
 //   TEST_PERF_T2(mhz, ms, float64x2, F)

#define TEST_PERF_ALL_T2(mhz, ms, F)                              \
    TEST_PERF_T2(mhz, ms, int8x16, F)                             \
    TEST_PERF_T2(mhz, ms, int16x8, F)                             \
    TEST_PERF_T2(mhz, ms, int32x4, F)                             \
    TEST_PERF_T2(mhz, ms, int64x2, F)                             \
    TEST_PERF_T2(mhz, ms, float32x4, F)                           \
 //   TEST_PERF_T2(mhz, ms, baseline, float64x2, F)

int main(int argc, char** argv)
{
    unsigned mhz, ms;

    if (argc < 3) {
        std::cerr << "Please specify the speed of the processor in MHz as the"
                     " first argument\n and the duration of each test in "
                     " milliseconds as the second \n";
        return 1;
    }
    mhz = std::stol(argv[1]);
    ms = std::stol(argv[2]);

    // logic
    TEST_PERF_ALL_T2(mhz,ms, bit_and);
    TEST_PERF_ALL_T2(mhz,ms, bit_or);
    TEST_PERF_ALL_T2(mhz,ms, bit_xor);

    // compare
    TEST_PERF_NO_I64_T2(mhz,ms, cmp_eq);
    TEST_PERF_NO_I64_T2(mhz,ms, cmp_neq);
    TEST_PERF_NO_I64_T2(mhz,ms, cmp_lt);
    TEST_PERF_NO_I64_T2(mhz,ms, cmp_gt);

    // convert
    TEST_PERF_T1(mhz,ms, int8x16, to_int16x8);
    TEST_PERF_T1(mhz,ms, uint8x16, to_int16x8);
    TEST_PERF_T1(mhz,ms, int16x8, to_int32x4);
    TEST_PERF_T1(mhz,ms, uint16x8, to_int32x4);
    TEST_PERF_T1(mhz,ms, float32x4, to_int32x4);
    TEST_PERF_T1(mhz,ms, int32x4, to_int64x2);
    TEST_PERF_T1(mhz,ms, uint32x4, to_int64x2);
    TEST_PERF_T1(mhz,ms, int32x4, to_float32x4);

    // math (many missing)
    TEST_PERF_ALL_T2(mhz,ms, add);
    TEST_PERF_ALL_T2(mhz,ms, sub);
    TEST_PERF_NO_I64_T2(mhz,ms, min);
    TEST_PERF_NO_I64_T2(mhz,ms, max);
    TEST_PERF_T2(mhz,ms, uint8x16, avg);
    TEST_PERF_T2(mhz,ms, uint16x8, avg);
    TEST_PERF_T2(mhz,ms, float32x4, mul);
    //TEST_PERF_T2(mhz,ms, float64x2, mul);
    TEST_PERF_T2(mhz,ms, int16x8, mul_lo);
    TEST_PERF_T2(mhz,ms, int16x8, mul_hi);
    TEST_PERF_T2(mhz,ms, int32x4, mul_lo);
    TEST_PERF_T2(mhz,ms, int16x8, mull_lo);
    TEST_PERF_T2(mhz,ms, int16x8, mull_hi);

    // shift
    //TEST_PERF_T1(mhz,ms, int16x8, shift_l);
    //TEST_PERF_T1(mhz,ms, int32x4, shift_l);
    //TEST_PERF_T1(mhz,ms, int64x2, shift_l);
    TEST_PERF_T1(mhz,ms, int16x8, shift_l<0>);
    TEST_PERF_T1(mhz,ms, int32x4, shift_l<0>);
    TEST_PERF_T1(mhz,ms, int64x2, shift_l<0>);
    TEST_PERF_T1(mhz,ms, int16x8, shift_l<2>);
    TEST_PERF_T1(mhz,ms, int32x4, shift_l<2>);
    TEST_PERF_T1(mhz,ms, int64x2, shift_l<2>);
    //TEST_PERF_T1(mhz,ms, int16x8, shift_r);
    //TEST_PERF_T1(mhz,ms, int32x4, shift_r);
    //TEST_PERF_T1(mhz,ms, int64x2, shift_r);
    TEST_PERF_T1(mhz,ms, int16x8, shift_r<0>);
    TEST_PERF_T1(mhz,ms, int32x4, shift_r<0>);
    TEST_PERF_T1(mhz,ms, int64x2, shift_r<0>);
    TEST_PERF_T1(mhz,ms, int16x8, shift_r<2>);
    TEST_PERF_T1(mhz,ms, int32x4, shift_r<2>);
    TEST_PERF_T1(mhz,ms, int64x2, shift_r<2>);

    // shuffle
    TEST_PERF_ALL_T2(mhz,ms, zip_lo);
    TEST_PERF_ALL_T2(mhz,ms, zip_hi);
    TEST_PERF_ALL_T2(mhz,ms, unzip_lo);
    TEST_PERF_ALL_T2(mhz,ms, unzip_hi);
    TEST_PERF_ALL_T1(mhz,ms, move_l<0>);
    TEST_PERF_ALL_T1(mhz,ms, move_l<1>);
    TEST_PERF_ALL_T1(mhz,ms, move_r<0>);
    TEST_PERF_ALL_T1(mhz,ms, move_r<1>);
    TEST_PERF_ALL_T1(mhz,ms, broadcast<0>);
    TEST_PERF_ALL_T1(mhz,ms, broadcast<1>);
    TEST_PERF_ALL_T2(mhz,ms, align<0>);
    TEST_PERF_ALL_T2(mhz,ms, align<1>);
}
