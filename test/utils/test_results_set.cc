/*  Copyright (C) 2012-2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "test_results_set.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <type_traits>
#include <typeinfo>
#include <string>

TestResultsSet::TestResultsSet(const char* name) :
    name_(name),
    curr_precision_ulp_(0),
    curr_fp_zero_equal_(false)
{
    reset_seq();
}

TestResultsSet::Result& TestResultsSet::push(ElementType type, unsigned length,
                                             const char* file, unsigned line)
{
    results_.emplace_back(type, length, element_size_for_type(type), file, line,
                          seq_++, curr_precision_ulp_, curr_fp_zero_equal_);
    return results_.back();
}

unsigned precision_for_result(const TestResultsSet::Result& res)
{
    switch (res.type) {
    case TYPE_FLOAT32:
    case TYPE_FLOAT64:
        return res.prec_ulp;
    default:
        return 0;
    }
}

template<class T> struct fix_char_type { using type = T; };
template<> struct fix_char_type<uint8_t> { using type = int; };
template<> struct fix_char_type<int8_t> { using type = int; };

template<class T>
void print_hex(std::ostream& err, unsigned num_elems, unsigned width,
               const T* p)
{
    static_assert(std::is_unsigned<T>::value, "T must be unsigned");
    err << "[ " << std::hex << std::setfill('0');
    err.precision(width);
    for (unsigned i = 0; i < num_elems; i++, p++) {
        err << std::setw(width*2) << uint64_t(*p);
        if (i != num_elems - 1) {
            err << " ; ";
        }
    }
    err << " ]";
    err << std::dec << std::setfill(' ');
}

template<class T>
void print_numeric(std::ostream& err, unsigned num_elems, unsigned precision,
                   const T* p)
{
    err << "[ ";
    err.precision(precision);
    for (unsigned i = 0; i < num_elems; i++, p++) {
        err << typename fix_char_type<T>::type(*p);
        if (i != num_elems - 1) {
            err << " ; ";
        }
    }
    err << " ]";
    err << std::dec;
}

void print_vector_hex(std::ostream& out, ElementType type, unsigned num_elems,
                      const void* data)
{
    switch (type) {
    case TYPE_UINT8:
        print_hex(out, num_elems, 1, (const uint8_t*)data);
        break;
    case TYPE_INT8:
        print_hex(out, num_elems, 1, (const uint8_t*)data);
        break;
    case TYPE_UINT16:
        print_hex(out, num_elems, 2, (const uint16_t*)data);
        break;
    case TYPE_INT16:
        print_hex(out, num_elems, 2, (const uint16_t*)data);
        break;
    case TYPE_UINT32:
        print_hex(out, num_elems, 4, (const uint32_t*)data);
        break;
    case TYPE_INT32:
        print_hex(out, num_elems, 4, (const uint32_t*)data);
        break;
    case TYPE_UINT64:
        print_hex(out, num_elems, 8, (const uint64_t*)data);
        break;
    case TYPE_INT64:
        print_hex(out, num_elems, 8, (const uint64_t*)data);
        break;
    case TYPE_FLOAT32:
        print_hex(out, num_elems, 4, (const uint32_t*)data);
        break;
    case TYPE_FLOAT64:
        print_hex(out, num_elems, 8, (const uint64_t*)data);
        break;
    }
}

void print_vector_numeric(std::ostream& out, ElementType type,
                          unsigned num_elems, const void* data)
{
    switch (type) {
    case TYPE_UINT8:
        print_numeric(out, num_elems, 4, (const int8_t*)data);
        break;
    case TYPE_INT8:
        print_numeric(out, num_elems, 4, (const uint8_t*)data);
        break;
    case TYPE_UINT16:
        print_numeric(out, num_elems, 6, (const int16_t*)data);
        break;
    case TYPE_INT16:
        print_numeric(out, num_elems, 6, (const uint16_t*)data);
        break;
    case TYPE_UINT32:
        print_numeric(out, num_elems, 11, (const int32_t*)data);
        break;
    case TYPE_INT32:
        print_numeric(out, num_elems, 11, (const uint32_t*)data);
        break;
    case TYPE_UINT64:
        print_numeric(out, num_elems, 20, (const int64_t*)data);
        break;
    case TYPE_INT64:
        print_numeric(out, num_elems, 20, (const uint64_t*)data);
        break;
    case TYPE_FLOAT32:
        print_numeric(out, num_elems, 7, (const float*)data);
        break;
    case TYPE_FLOAT64:
        print_numeric(out, num_elems, 17, (const double*)data);
        break;
    }
}

const char* vector_type_to_str(ElementType type)
{
    switch (type) {
    case TYPE_UINT8: return "uint8";
    case TYPE_INT8: return "int8";
    case TYPE_UINT16: return "uint16";
    case TYPE_INT16: return "int16";
    case TYPE_UINT32: return "uint32";
    case TYPE_INT32: return "int32";
    case TYPE_UINT64: return "uint64";
    case TYPE_INT64: return "int64";
    case TYPE_FLOAT32: return "float32";
    case TYPE_FLOAT64: return "float64";
    default: return "UNDEFINED";
    }
}

void print_data_diff(std::ostream& out, ElementType type, unsigned num_elems,
                     const void* data_a, const void* data_b)
{
    out << "type: " << vector_type_to_str(type)
        << " count: " << num_elems
        << " size: " << element_size_for_type(type) * num_elems << " bytes"
        << "\n";
    out << "A : ";
    print_vector_numeric(out, type, num_elems, data_a);
    out << "\nA : ";
    print_vector_hex(out, type, num_elems, data_a);
    out << "\nB : ";
    print_vector_numeric(out, type, num_elems, data_b);
    out << "\nB : ";
    print_vector_hex(out, type, num_elems, data_b);
    out << "\n";
}

void print_separator(std::ostream& out)
{
    out << "--------------------------------------------------------------\n";
}

void print_file_info(std::ostream& out, const char* file)
{
    if (file == nullptr) {
        file = "<unknown>";
    }
    out << "  In file \"" << file << "\" :\n";
}

void print_file_info(std::ostream& out, const char* file, unsigned line)
{
    if (file == nullptr) {
        file = "<unknown>";
    }
    out << "  In file \"" << file << "\" at line " << line << " : \n";
}

void print_arch(std::ostream& out, const char* a_arch, const char* b_arch)
{
    out << "  For architectures: " << a_arch << " and " << b_arch << " :\n";
}

void print_test_case_name(std::ostream& out, const char* name)
{
    out << "  In test case \"" << name << "\" :\n";
}

void print_seq_num(std::ostream& out, unsigned num)
{
    out << "  Sequence number: " << num << "\n";
}

void print_precision(std::ostream& out, unsigned prec)
{
    if (prec > 0) {
        out << "  Precision: " << prec << "ULP\n";
    }
}

template<class T>
struct binary_for_float;
template<> struct binary_for_float<float> { using type = int32_t; };
template<> struct binary_for_float<double> { using type = int64_t; };

template<class U, class T>
U binary_convert(const T& x)
{
    U r;
    std::memcpy(&r, &x, sizeof(r));
    return r;
}

template<class T>
bool is_zero_or_neg_zero(T x)
{
    typedef typename binary_for_float<T>::type IntT;
    IntT zero = binary_convert<IntT>(T(0.0));
    IntT neg_zero = binary_convert<IntT>(T(-0.0));
    IntT ix = binary_convert<IntT>(x);
    return ix == zero || ix == neg_zero;
}

// Do not depend on floating-point operations when performing tests as flush
// to zero may be enabled and wrong results may be reported. Assume IEEE-754
// floating-number format and perform everything using integer operations.
template<class T>
T nextafter_ulps(T from, T to)
{
    // ignore NaNs
    if (std::isnan(from) || std::isnan(to))
        return from;

    // if 'from' is infinity, ignore
    if (from == std::numeric_limits<T>::infinity() ||
        from == -std::numeric_limits<T>::infinity())
    {
        return from;
    }

    typedef typename binary_for_float<T>::type IntT;
    IntT from_i = binary_convert<IntT>(from);
    IntT to_i = binary_convert<IntT>(to);

    // do nothing if 'from' already equals 'to'
    if (from_i == to_i)
        return from;

    IntT zero = binary_convert<IntT>(T(0.0));
    IntT neg_zero = binary_convert<IntT>(T(-0.0));

    // handle sign wraparound at zero
    if (from_i == zero && (to_i < 0 || to_i == neg_zero))
        return T(-0.0);
    if (from_i == neg_zero && (to_i > 0 || to_i == zero))
        return T(0.0);

    // fortunately IEEE-754 format is such that one ULPS can be added or
    // subtracted with simple integer addition or subtraction, except in two
    // cases: when the source number is infinity or the operation would change
    // the sign of the argument (it's zero).

    if (from_i < to_i)
        from_i += 1;
    else
        from_i -= 1;

    return binary_convert<T>(from_i);
}

// T is either double or float
template<class T>
bool cmpeq_arrays(const T* a, const T* b, unsigned num_elems,
                  unsigned prec, bool zero_eq)
{
    for (unsigned i = 0; i < num_elems; i++) {
        // we need to be extra-precise here. nextafter is used because it won't
        // introduce any rounding errors
        T ia = *a++;
        T ib = *b++;
        if (std::isnan(ia) && std::isnan(ib)) {
            continue;
        }
        if (zero_eq && is_zero_or_neg_zero(ia) && is_zero_or_neg_zero(ib)) {
            continue;
        }
        for (unsigned i = 0; i < prec; i++) {
            ia = nextafter_ulps(ia, ib);
        }
        if (std::memcmp(&ia, &ib, sizeof(ia)) != 0) {
            return false;
        }
    }
    return true;
}

const char* get_filename_from_results_set(const TestResultsSet& a)
{
    if (a.results().empty())
        return nullptr;
    return a.results().front().file;
}

const char* get_filename_from_results_set(const TestResultsSet& a,
                                          const TestResultsSet& b)
{
    const char* res = get_filename_from_results_set(a);
    if (res)
        return res;
    return get_filename_from_results_set(b);
}

struct TestSequence {
    unsigned begin_index, end_index;
    const char* begin_file;
    // For comparisons we want to strip the arch suffix from the file name.
    // To reduce the number of duplicate computations it is cached here.
    std::string begin_file_stripped;
    unsigned begin_line;
};

bool is_test_seq_from_same_test(const TestSequence& a, const TestSequence& b)
{
    if (a.begin_file_stripped != b.begin_file_stripped)
        return false;
    if (a.begin_line != b.begin_line)
        return false;
    return true;
}

using TestSequenceList = std::vector<TestSequence>;

/*  Skips test result sequences until two results referring to the same test
    are found. If a[ia] and b[ib] refers to the same test already, nothing is
    done.

    Returns true if test results were skipped, false otherwise.
*/
bool skip_results_until_same_test(unsigned& ia, unsigned& ib,
                                  const TestSequenceList& a,
                                  const TestSequenceList& b)
{
    if (is_test_seq_from_same_test(a[ia], b[ib]))
        return false;
    unsigned max_skipped = a.size() - ia + b.size() - ib;

    // This problem is solved by brute force as the number of skipped sequences
    // is very likely small. We evaluate all possible ways to skip sequences
    // starting with the smallest total number of skipped sequences.
    for (unsigned num_skipped = 1; num_skipped < max_skipped; ++num_skipped) {

        for (unsigned i = 0; i <= num_skipped; ++i) {
            unsigned skip_from_a = i;
            unsigned skip_from_b = num_skipped - i;

            unsigned new_ia = ia + skip_from_a;
            unsigned new_ib = ib + skip_from_b;

            if (new_ia < a.size() && new_ib < b.size()) {
                if (is_test_seq_from_same_test(a[new_ia], b[new_ib])) {
                    ia = new_ia;
                    ib = new_ib;
                    return true;
                }
            }
        }
    }
    // could not find any matching tests
    ia = a.size();
    ib = b.size();
    return true;
}

std::string strip_arch_suffix_from_file(const char* file)
{
    if (file == nullptr)
        return "";
    std::string ret = file;
    std::string::size_type idx = ret.find("_simdpp_");
    if (idx != std::string::npos)
        ret = ret.substr(0, idx);
    return ret;
}

TestSequenceList build_test_sequences(const std::vector<TestResultsSet::Result>& results)
{
    TestSequenceList ret;
    if (results.empty())
        return ret;

    TestSequence next_seq;

    unsigned i = 0;
    next_seq.begin_index = i;
    next_seq.begin_file = results[i].file;
    next_seq.begin_file_stripped = strip_arch_suffix_from_file(results[i].file);
    next_seq.begin_line = results[i].line;
    unsigned last_seq_num = results[i].seq;

    ++i;

    for (; i < results.size(); ++i) {
        if (results[i].seq <= last_seq_num) {
            next_seq.end_index = i;
            ret.push_back(next_seq);

            next_seq.begin_index = i;
            next_seq.begin_file = results[i].file;
            next_seq.begin_file_stripped = strip_arch_suffix_from_file(results[i].file);
            next_seq.begin_line = results[i].line;
        }
        last_seq_num = results[i].seq;
    }

    next_seq.end_index = i;
    ret.push_back(next_seq);

    return ret;
}

bool cmpeq_result(const TestResultsSet::Result& ia, const TestResultsSet::Result& ib,
                  unsigned fp_prec, bool fp_zero_eq)
{
    if (std::memcmp(ia.d(), ib.d(), ia.el_size * ia.length) == 0) {
        return true;
    }

    switch (ia.type) {
    case TYPE_FLOAT32:
        return cmpeq_arrays((const float*)ia.d(), (const float*)ib.d(), ia.length,
                            fp_prec, fp_zero_eq);
    case TYPE_FLOAT64:
        return cmpeq_arrays((const double*)ia.d(), (const double*)ib.d(), ia.length,
                            fp_prec, fp_zero_eq);
    default:
        return false;
    }
}

void report_test_comparison(const TestResultsSet& a, const char* a_arch,
                            const TestResultsSet& b, const char* b_arch,
                            TestReporter& tr)
{
    // Handle fatal errors first
    if (std::strcmp(a.name(), b.name()) != 0) {
        print_separator(tr.out());
        print_arch(tr.out(), a_arch, b_arch);
        print_file_info(tr.out(), get_filename_from_results_set(a, b));
        tr.out() << "FATAL: Test case names do not match: \""
                 << a.name() << "\" and \""  << b.name() << "\"\n";
        print_separator(tr.out());
        tr.add_result(false);
        return;
    }

    TestSequenceList a_seqs = build_test_sequences(a.results());
    TestSequenceList b_seqs = build_test_sequences(b.results());

    // Compare results
    unsigned ia_seq = 0;
    unsigned ib_seq = 0;

    while (ia_seq < a_seqs.size() && ib_seq < b_seqs.size()) {
        if (skip_results_until_same_test(ia_seq, ib_seq, a_seqs, b_seqs)) {
            continue;
        }

        const auto& a_seq = a_seqs[ia_seq];
        const auto& b_seq = b_seqs[ib_seq];

        unsigned a_seq_size = a_seq.end_index - a_seq.begin_index;
        unsigned b_seq_size = b_seq.end_index - b_seq.begin_index;

        if (a_seq_size != b_seq_size) {
            print_separator(tr.out());
            print_arch(tr.out(), a_arch, b_arch);
            tr.out() << "Sequence A starting at:\n";
            print_file_info(tr.out(), a_seq.begin_file, a_seq.begin_line);
            tr.out() << "Sequence B starting at:\n";
            print_file_info(tr.out(), b_seq.begin_file, b_seq.begin_line);
            print_test_case_name(tr.out(), a.name());
            tr.out() << "FATAL: The number of results in a test sequence do "
                     << "not match: "
                     << " result count: "
                     << a_seq_size << "/" << b_seq_size << "\n";
            print_separator(tr.out());
            tr.add_result(false);
            return;
        }

        for (unsigned i = 0; i < a_seq_size; ++i) {
            unsigned ia = a_seq.begin_index + i;
            unsigned ib = b_seq.begin_index + i;

            const auto& a_res = a.results()[ia];
            const auto& b_res = b.results()[ib];

            if ((a_res.seq != b_res.seq) ||
                (a_res.line != b_res.line) ||
                (a_res.type != b_res.type) ||
                (a_res.length != b_res.length))
            {
                print_separator(tr.out());
                print_arch(tr.out(), a_arch, b_arch);
                tr.out() << "Sequence A starting at:\n";
                print_file_info(tr.out(), a_seq.begin_file, a_seq.begin_line);
                tr.out() << "Sequence B starting at:\n";
                print_file_info(tr.out(), b_seq.begin_file, b_seq.begin_line);
                print_test_case_name(tr.out(), a.name());
                if (a_res.seq != b_res.seq) {
                    tr.out() << "FATAL: Sequence numbers do not match for "
                             << "items in the same sequence position:"
                             << " seq_A: " << a_res.seq
                             << " seq_B: " << b_res.seq << "\n";
                }
                if (a_res.line != b_res.line) {
                    tr.out() << "FATAL: Line numbers do not match for items "
                             << "with the same sequence position:"
                             << " seq: " << a_res.seq
                             << " line_A: " << a_res.line
                             << " line_B: " << b_res.line << "\n";
                }
                if (a_res.type != b_res.type) {
                    tr.out() << "FATAL: Types do not match for items with the "
                             << "same sequence position:"
                             << " seq: " << a_res.seq
                             << " type_A: " << vector_type_to_str(a_res.type)
                             << " type_B: " << vector_type_to_str(b_res.type) << "\n";
                }
                if (a_res.length != b_res.length) {
                    tr.out() << "FATAL: Number of elements do not match for "
                             << "items with the same sequence position:"
                             << " seq: " << a_res.seq
                             << " length_A: " << a_res.length
                             << " length_B: " << b_res.length << "\n";
                }
                print_separator(tr.out());
                tr.add_result(false);
                return;
            }

            unsigned prec = std::max(precision_for_result(a_res),
                                     precision_for_result(b_res));

            bool fp_zero_eq = a_res.fp_zero_eq || b_res.fp_zero_eq;

            if (!cmpeq_result(a_res, b_res, prec, fp_zero_eq)) {
                print_separator(tr.out());
                print_arch(tr.out(), a_arch, b_arch);
                print_file_info(tr.out(), a_res.file, a_res.line);
                print_test_case_name(tr.out(), a.name());
                print_seq_num(tr.out(), a_res.seq);
                tr.out() << "ERROR: Vectors not equal: \n";
                print_data_diff(tr.out(), a_res.type, a_res.length, a_res.d(), b_res.d());
                print_precision(tr.out(), prec);
                print_separator(tr.out());
                tr.add_result(false);
            } else {
                tr.add_result(true);
            }

        }
        ia_seq++;
        ib_seq++;
    }
}
