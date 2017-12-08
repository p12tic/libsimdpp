/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TEST_RESULTS_SET_H
#define LIBSIMDPP_TEST_TEST_RESULTS_SET_H

#include <vector>
#include <cstring>
#include <iosfwd>
#include <cstdint>
#include "test_reporter.h"
#include "element_type.h"

// Prints two vectors side by side for comparison
void print_data_diff(std::ostream& out, ElementType type, unsigned num_elems,
                     const void* data_a, const void* data_b);

void print_separator(std::ostream& out);
void print_file_info(std::ostream& out, const char* file);
void print_file_info(std::ostream& out, const char* file, unsigned line);

void print_vector_hex(std::ostream& out, ElementType type, unsigned num_elems,
                      const void* data);

void print_vector_numeric(std::ostream& out, ElementType type,
                          unsigned num_elems, const void* data);

/** The class represents test results for certain instruction set. We later
    compare the results with other instruction sets and assume that all
    differences are errors. It's possible to set the precision of each test
    result so that the differencies less than the set precision are not
    interpreted as errors.
*/
class TestResultsSet {
public:

    // Holds one result vector
    struct Result {
        static const unsigned num_bytes = 32;

        Result(ElementType atype, unsigned alength, unsigned ael_size,
               const char* afile, unsigned aline, unsigned aseq,
               unsigned aprec_ulp, bool afp_zero_eq)
        {
            type = atype;
            file = afile;
            line = aline;
            seq = aseq;
            prec_ulp = aprec_ulp;
            fp_zero_eq = afp_zero_eq;
            length = alength;
            el_size = ael_size;
            data.resize(el_size*length);
        }

        ElementType type;
        unsigned line;
        unsigned seq;
        unsigned prec_ulp;
        bool fp_zero_eq;
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
    Result& push(ElementType type, unsigned length, const char* file, unsigned line);

    /// Sets the allowed error in ULPs. Only meaningful for floating-point data.
    /// Affects all pushed data until the next call to @a unset_precision
    void set_precision(unsigned num_ulp)    { curr_precision_ulp_ = num_ulp; }
    void unset_precision()                  { curr_precision_ulp_ = 0; }

    /// Sets whether floating-point zero and negative zero are considered
    /// equal. Affects all pushed data until the next call to @a unset_fp_zero_equal
    void set_fp_zero_equal()                { curr_fp_zero_equal_ = true; }
    void unset_fp_zero_equal()              { curr_fp_zero_equal_ = false; }

    /// The name of the test case
    const char* name() const                { return name_; }

    /// Resets the sequence number
    void reset_seq()                        { seq_ = 0; }

    const std::vector<Result>& results() const { return results_; }

private:
    friend class TestResults;

    TestResultsSet(const char* name);

    const char* name_;
    unsigned seq_;
    unsigned curr_precision_ulp_;
    bool curr_fp_zero_equal_;

    std::vector<Result> results_;
};

/** Compares two results sets.

    Each test result is identified by the source file name, line number in that
    file and sequence number. If that data is equal for two test results, they
    are said to refer to the same test.

    The same source line must produce the same number of test results. That is,
    the minimum and maximum sequence numbers must be the same in each group of
    test results that are produced from that line. Note that each group of
    increasing sequence numbers may be produced from different source lines.

    Any differences in reported values for the test results referring to the
    same test are interpreted as errors and printed to the test reporter.

    The test results sets may contain different sets of test results, that is,
    on certain architecture part of the tests may be excluded from running. If
    during iteration of the results set test results start to refer to
    different tests, the result set is examined to find the next pair of test
    results that refer to the same test. An attempt is made to skip as few
    results as possible.
*/
void report_test_comparison(const TestResultsSet& a, const char* a_arch,
                            const TestResultsSet& b, const char* b_arch,
                            TestReporter& tr);
#endif
