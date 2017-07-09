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
#include "vector_type.h"

class TestResultsSet;

void report_test_comparison(const TestResultsSet& a, const char* a_arch,
                            const TestResultsSet& b, const char* b_arch,
                            TestReporter& tr);

// Prints two vectors side by side for comparison
void print_vector_diff(std::ostream& out, unsigned type, unsigned num_elems,
                       const void* data_a, const void* data_b);

void print_separator(std::ostream& out);
void print_file_info(std::ostream& out, const char* file);
void print_file_info(std::ostream& out, const char* file, unsigned line);

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

        Result(VectorType atype, unsigned alength, unsigned ael_size,
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

        VectorType type;
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
    Result& push(VectorType type, unsigned length, const char* file, unsigned line);

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
    void reset_seq()                        { seq_ = 1; }

    /** Allows synchronizing tests in cases when certain architectures do not
        execute the test in question. The function must be called before and
        after the block of tests that may not be executed. The call to this
        function must be executed regardless of architectures.

        The function resets the sequence number.
    */
    void sync_archs()                       { curr_results_section_++; reset_seq(); }

    const std::vector<std::vector<Result>>& results() const { return results_; }

private:
    friend class TestResults;

    TestResultsSet(const char* name);

    const char* name_;
    unsigned seq_;
    unsigned curr_precision_ulp_;
    unsigned curr_fp_zero_equal_;

    unsigned curr_results_section_;
    std::vector<std::vector<Result>> results_;
};

#endif
