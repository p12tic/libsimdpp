/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TEST_SUITE_H
#define LIBSIMDPP_TEST_TEST_SUITE_H

#include <vector>
#include <cstring>
#include <iosfwd>
#include <cstdint>

class TestSuite;

bool test_equal(const TestSuite& a, const char* a_arch,
                const TestSuite& b, const char* b_arch,
                std::ostream& err);

class TestSuite {
public:

    // Types of vector elements
    enum Type : uint8_t {
        TYPE_INT8 = 0,
        TYPE_UINT8,
        TYPE_INT16,
        TYPE_UINT16,
        TYPE_UINT32,
        TYPE_INT32,
        TYPE_UINT64,
        TYPE_INT64,
        TYPE_FLOAT32,
        TYPE_FLOAT64
    };

    // Holds one result vector
    struct Result {
        static const unsigned num_bytes = 32;

        Result(Type atype, unsigned alength, unsigned ael_size, unsigned aline,
               unsigned aseq, unsigned aprec_ulp)
        {
            type = atype;
            line = aline;
            seq = aseq;
            prec_ulp = aprec_ulp;
            length = alength;
            el_size = ael_size;
            data.resize(el_size*length);
        }

        Type type;
        unsigned line;
        unsigned seq;
        unsigned prec_ulp;
        const char* file;
        unsigned length;
        unsigned el_size;

        void set(unsigned id, void* adata)
        {
            std::memcpy(data.data() + id*el_size, adata, el_size);
        }

        const void* d() const
        {
            return data.data();
        }

        std::vector<std::uint8_t> data;
    };

    /// Stores the results into the results set.
    Result& push(Type type, unsigned length, unsigned line);

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
    friend class TestResults;
    friend bool test_equal(const TestSuite& a, const char* a_arch,
                           const TestSuite& b, const char* b_arch,
                           std::ostream& err);

    TestSuite(const char* name, const char* file);

    static std::size_t size_for_type(Type t);
    static unsigned precision_for_result(const Result& res);

    const char* name_;
    const char* file_;
    unsigned seq_;
    unsigned curr_precision_ulp_;
    std::vector<Result> results_;
};



#endif
