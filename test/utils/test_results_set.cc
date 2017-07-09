/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "test_results_set.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <type_traits>
#include <typeinfo>
#include <cstdlib>

TestResultsSet::TestResultsSet(const char* name) :
    name_(name),
    curr_precision_ulp_(0),
    curr_fp_zero_equal_(false),
    curr_results_section_(0)
{
    reset_seq();
}

TestResultsSet::Result& TestResultsSet::push(VectorType type, unsigned length,
                                             const char* file, unsigned line)
{
    while (results_.size() <= curr_results_section_)
        results_.push_back(std::vector<Result>());

    auto& curr_part = results_[curr_results_section_];
    curr_part.emplace_back(type, length, element_size_for_type(type), file, line, seq_++,
                           curr_precision_ulp_, curr_fp_zero_equal_);
    return curr_part.back();
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

void print_vector_hex(std::ostream& out, unsigned type, unsigned num_elems,
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

void print_vector_numeric(std::ostream& out, unsigned type, unsigned num_elems,
                          const void* data)
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

void print_vector_diff(std::ostream& out, unsigned type, unsigned num_elems,
                       const void* data_a, const void* data_b)
{
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
    if (a.results().front().empty())
        return nullptr;
    return a.results().front().front().file;
}

const char* get_filename_from_results_set(const TestResultsSet& a,
                                          const TestResultsSet& b)
{
    const char* res = get_filename_from_results_set(a);
    if (res)
        return res;
    return get_filename_from_results_set(b);
}

void report_test_comparison(const TestResultsSet& a, const char* a_arch,
                            const TestResultsSet& b, const char* b_arch,
                            TestReporter& tr)
{
    auto print_arch = [&]()
    {
        tr.out() << "  For architectures: " << a_arch << " and " << b_arch << " :\n";
    };
    auto fmt_test_case = [&]()
    {
        tr.out() << "  In test case \"" << a.name() << "\" :\n";
    };
    auto fmt_seq = [&](unsigned num)
    {
        tr.out() << "  Sequence number: " << num << "\n"; // start from one
    };
    auto fmt_prec = [&](unsigned prec)
    {
        if (prec > 0) {
            tr.out() << "  Precision: " << prec << "ULP\n";
        }
    };

    auto type_str = [&](unsigned type) -> const char*
    {
        switch (type) {
        case TYPE_UINT8: return "uint86";
        case TYPE_INT8: return "int86";
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
    };

    auto cmpeq_result = [](const TestResultsSet::Result& ia, const TestResultsSet::Result& ib,
                           unsigned fp_prec, unsigned fp_zero_eq) -> bool
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
    };


    // Handle fatal errors first
    if (std::strcmp(a.name(), b.name()) != 0) {
        print_separator(tr.out());
        print_arch();
        print_file_info(tr.out(), get_filename_from_results_set(a, b));
        tr.out() << "FATAL: Test case names do not match: \""
                 << a.name() << "\" and \""  << b.name() << "\"\n";
        print_separator(tr.out());
        tr.add_result(false);
        return;
    }

    if (a.results().size() != b.results().size()) {
        if (a.results().size() == 0 || b.results().size() == 0) {
            return; // Ignore empty result sets
        }
        print_separator(tr.out());
        print_arch();
        print_file_info(tr.out(), get_filename_from_results_set(a, b));
        fmt_test_case();
        tr.out() << "FATAL: The number of result sections do not match: "
                 << a.results().size() << "/" << b.results().size() << "\n";
        print_separator(tr.out());
        tr.add_result(false);
        return;
    }

    // Compare results
    for (unsigned is = 0; is < a.results().size(); is++) {
        const auto& sect_a = a.results()[is];
        const auto& sect_b = b.results()[is];

        if (sect_a.empty() || sect_b.empty())
            continue;

        if (sect_a.size() != sect_b.size()) {
            print_separator(tr.out());
            print_arch();
            print_file_info(tr.out(), sect_a.front().file);
            fmt_test_case();
            tr.out() << "FATAL: The number of results in a section do not match: "
                     << " section: " << is << " result count: "
                     << sect_a.size() << "/" << sect_b.size() << "\n";
            print_separator(tr.out());
            tr.add_result(false);
        }

        for (unsigned i = 0; i < sect_a.size(); ++i) {
            const auto& ia = sect_a[i];
            const auto& ib = sect_b[i];

            if ((ia.line != ib.line) || (ia.type != ib.type) || (ia.length != ib.length)) {
                print_separator(tr.out());
                print_arch();
                print_file_info(tr.out(), ia.file, ia.line);
                fmt_test_case();
                if (ia.line != ib.line) {
                    tr.out() << "FATAL: Line numbers do not match for items with the same "
                             << "sequence number: section: " << is << " id: " << i
                             << " line_A: " << ia.line
                             << " line_B: " << ib.line << "\n";
                }
                if (ia.type != ib.type) {
                    tr.out() << "FATAL: Types do not match for items with the same "
                             << "sequence number: id: " << i
                             << " type_A: " << type_str(ia.type)
                             << " type_B: " << type_str(ib.type) << "\n";
                }
                if (ia.length != ib.length) {
                    tr.out() << "FATAL: Number of elements do not match for "
                             << "items with the same sequence number: id: " << i
                             << " length_A: " << ia.length
                             << " length_B: " << ib.length << "\n";
                }
                print_separator(tr.out());
                tr.add_result(false);
                return;
            }

            unsigned prec = std::max(precision_for_result(ia),
                                     precision_for_result(ib));

            bool fp_zero_eq = ia.fp_zero_eq || ib.fp_zero_eq;

            if (!cmpeq_result(ia, ib, prec, fp_zero_eq)) {
                print_separator(tr.out());
                print_arch();
                print_file_info(tr.out(), ia.file, ia.line);
                fmt_test_case();
                fmt_seq(ia.seq);
                tr.out() << "ERROR: Vectors not equal: \n";
                print_vector_diff(tr.out(), ia.type, ia.length, ia.d(), ib.d());
                fmt_prec(prec);
                print_separator(tr.out());
                tr.add_result(false);
            } else {
                tr.add_result(true);
            }
        }
    }
}
