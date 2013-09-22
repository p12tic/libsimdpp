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

#ifndef LIBSIMDPP_TEST_TEST_CASE_H
#define LIBSIMDPP_TEST_TEST_CASE_H

#include <vector>
#include <cstring>
#include <iosfwd>
#include <cstdint>

class TestCase;

bool test_equal(const TestCase& a, const char* a_arch,
                const TestCase& b, const char* b_arch,
                std::ostream& err);

class TestCase {
public:

    // Types of 16-bit vectors
    enum Type : uint8_t {
        // 16-bit number
        TYPE_UINT16 = 0,
        // 16-byte vector
        TYPE_UINT8x16,
        TYPE_INT8x16,
        TYPE_UINT16x8,
        TYPE_INT16x8,
        TYPE_UINT32x4,
        TYPE_INT32x4,
        TYPE_UINT64x2,
        TYPE_INT64x2,
        TYPE_FLOAT32x4,
        TYPE_FLOAT64x2,
        // 32-byte vector
        TYPE_UINT8x32,
        TYPE_INT8x32,
        TYPE_UINT16x16,
        TYPE_INT16x16,
        TYPE_UINT32x8,
        TYPE_INT32x8,
        TYPE_UINT64x4,
        TYPE_INT64x4,
        TYPE_FLOAT32x8,
        TYPE_FLOAT64x4,
    };

    /// Stores the results into the results set.
    void push(Type type, void* data, unsigned line);

    /// Sets the allowed error in ULPs. Only meaningful for floating-point data.
    /// Affects all pushed data until the next call to @a unset_precision
    void set_precision(unsigned num_ulp)    { curr_precision_ulp_ = num_ulp; }
    void unset_precision()                  { curr_precision_ulp_ = 0; }

    /// The name of the test case
    const char* name() const                { return name_; }

    /// Resets the sequence number
    void reset_seq()                        { seq_ = 1; }

    /// The number of results pushed to the test case
    std::size_t num_results() const         { return results_.size(); }

private:
    class Result;
    friend class TestResults;
    friend bool test_equal(const TestCase& a, const char* a_arch,
                           const TestCase& b, const char* b_arch,
                           std::ostream& err);

    TestCase(const char* name, const char* file);

    static std::size_t size_for_type(Type t);
    static unsigned precision_for_result(const Result& res);

    // Holds one result vector
    struct Result {
        static constexpr unsigned num_bytes = 32;

        Result(Type atype, void* adata, std::size_t asize,
               unsigned aline, unsigned aseq, unsigned aprec_ulp)
        {
            type = atype;
            line = aline;
            seq = aseq;
            prec_ulp = aprec_ulp;
            std::memcpy(v_u8, adata, asize);
        }

        Type type;
        unsigned line;
        unsigned seq;
        unsigned prec_ulp;
        const char* file;

        union {
            uint16_t u16;

            uint8_t v_u8[num_bytes];
            int8_t v_s8[num_bytes];
            uint16_t v_u16[num_bytes/2];
            int16_t v_s16[num_bytes/2];
            uint32_t v_u32[num_bytes/4];
            int32_t v_s32[num_bytes/4];
            uint64_t v_u64[num_bytes/8];
            int64_t v_s64[num_bytes/8];
            float v_f32[num_bytes/4];
            double v_f64[num_bytes/8];
        };
    };

    const char* name_;
    const char* file_;
    unsigned seq_;
    unsigned curr_precision_ulp_;
    std::vector<Result> results_;
};



#endif
