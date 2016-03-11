/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "test_suite.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <type_traits>
#include <typeinfo>
#include <cstdlib>

TestSuite::TestSuite(const char* name, const char* file) :
    name_(name),
    file_(file),
    curr_precision_ulp_(0),
    curr_fp_zero_equal_(false),
    curr_results_section_(0)
{
    reset_seq();
}

TestSuite::Result& TestSuite::push(Type type, unsigned length, unsigned line)
{
    while (results_.size() <= curr_results_section_)
        results_.push_back(std::vector<Result>());

    auto& curr_part = results_[curr_results_section_];
    curr_part.emplace_back(type, length, size_for_type(type), line, seq_++,
                           curr_precision_ulp_, curr_fp_zero_equal_);
    return curr_part.back();
}

std::size_t TestSuite::num_results() const
{
    std::size_t r = 0;
    for (const auto& sect: results_) {
        r += sect.size();
    }
    return r;
}

std::size_t TestSuite::size_for_type(Type t)
{
    switch (t) {
    case TYPE_INT8:
    case TYPE_UINT8: return 1;
    case TYPE_INT16:
    case TYPE_UINT16: return 2;
    case TYPE_UINT32:
    case TYPE_INT32: return 4;
    case TYPE_UINT64:
    case TYPE_INT64: return 8;
    case TYPE_FLOAT32: return 4;
    case TYPE_FLOAT64: return 8;
    default: std::abort();
    }
}

unsigned TestSuite::precision_for_result(const Result& res)
{
    switch (res.type) {
    case TestSuite::TYPE_FLOAT32:
    case TestSuite::TYPE_FLOAT64:
        return res.prec_ulp;
    default:
        return 0;
    }
}

template<class T> struct fix_char_type { using type = T; };
template<> struct fix_char_type<uint8_t> { using type = int; };
template<> struct fix_char_type<int8_t> { using type = int; };

template<class T>
void fmt_hex(std::ostream& err, unsigned num_elems, unsigned width,
             const char* prefix, const T* p)
{
    static_assert(std::is_unsigned<T>::value, "T must be unsigned");
    err << prefix << "[ " << std::hex << std::setfill('0');
    err.precision(width);
    for (unsigned i = 0; i < num_elems; i++, p++) {
        err << std::setw(width*2) << uint64_t(*p);
        if (i != num_elems - 1) {
            err << " ; ";
        }
    }
    err << " ]\n";
    err << std::dec << std::setfill(' ');
}

template<class T>
void fmt_num(std::ostream& err, unsigned num_elems, unsigned precision,
             const char* prefix, const T* p)
{
    err << prefix << "[ ";
    err.precision(precision);
    for (unsigned i = 0; i < num_elems; i++, p++) {
        err << typename fix_char_type<T>::type(*p);
        if (i != num_elems - 1) {
            err << " ; ";
        }
    }
    err << " ]\n";
    err << std::dec;
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

bool test_equal(const TestSuite& a, const char* a_arch,
                const TestSuite& b, const char* b_arch,
                std::ostream& err)

{
    auto fmt_separator = [&]()
    {
        err << "--------------------------------------------------------------\n";
    };
    auto fmt_arch = [&]()
    {
        err << "  For architectures: " << a_arch << " and " << b_arch << " :\n";
    };
    auto fmt_file = [&]()
    {
        fmt_arch();
        err << "  In file \"" << a.file_ << "\" :\n";
    };
    auto fmt_file_line = [&](unsigned line)
    {
        fmt_arch();
        err << "  In file \"" << a.file_ << "\" at line " << line << " : \n";
    };
    auto fmt_test_case = [&]()
    {
        err << "  In test case \"" << a.name_ << "\" :\n";
    };
    auto fmt_seq = [&](unsigned num)
    {
        err << "  Sequence number: " << num << "\n"; // start from one
    };
    auto fmt_prec = [&](unsigned prec)
    {
        if (prec > 0) {
            err << "  Precision: " << prec << "ULP\n";
        }
    };

    auto type_str = [&](unsigned type) -> const char*
    {
        switch (type) {
        case TestSuite::TYPE_UINT8: return "uint86";
        case TestSuite::TYPE_INT8: return "int86";
        case TestSuite::TYPE_UINT16: return "uint16";
        case TestSuite::TYPE_INT16: return "int16";
        case TestSuite::TYPE_UINT32: return "uint32";
        case TestSuite::TYPE_INT32: return "int32";
        case TestSuite::TYPE_UINT64: return "uint64";
        case TestSuite::TYPE_INT64: return "int64";
        case TestSuite::TYPE_FLOAT32: return "float32";
        case TestSuite::TYPE_FLOAT64: return "float64";
        default: return "UNDEFINED";
        }
    };

    auto fmt_vector = [&](const TestSuite::Result& r, const char* prefix) -> void
    {
        switch (r.type) {
        case TestSuite::TYPE_UINT8:
            fmt_hex(err, r.length, 1, prefix, (const uint8_t*)r.d());
            fmt_num(err, r.length, 4, prefix, (const int8_t*)r.d());
            break;
        case TestSuite::TYPE_INT8:
            fmt_hex(err, r.length, 1, prefix, (const uint8_t*)r.d());
            fmt_num(err, r.length, 4, prefix, (const uint8_t*)r.d());
            break;
        case TestSuite::TYPE_UINT16:
            fmt_hex(err, r.length, 2, prefix, (const uint16_t*)r.d());
            fmt_num(err, r.length, 6, prefix, (const int16_t*)r.d());
            break;
        case TestSuite::TYPE_INT16:
            fmt_hex(err, r.length, 2, prefix, (const uint16_t*)r.d());
            fmt_num(err, r.length, 6, prefix, (const uint16_t*)r.d());
            break;
        case TestSuite::TYPE_UINT32:
            fmt_hex(err, r.length, 4, prefix, (const uint32_t*)r.d());
            fmt_num(err, r.length, 11, prefix, (const int32_t*)r.d());
            break;
        case TestSuite::TYPE_INT32:
            fmt_hex(err, r.length, 4, prefix, (const uint32_t*)r.d());
            fmt_num(err, r.length, 11, prefix, (const uint32_t*)r.d());
            break;
        case TestSuite::TYPE_UINT64:
            fmt_hex(err, r.length, 8, prefix, (const uint64_t*)r.d());
            fmt_num(err, r.length, 20, prefix, (const int64_t*)r.d());
            break;
        case TestSuite::TYPE_INT64:
            fmt_hex(err, r.length, 8, prefix, (const uint64_t*)r.d());
            fmt_num(err, r.length, 20, prefix, (const uint64_t*)r.d());
            break;
        case TestSuite::TYPE_FLOAT32:
            fmt_hex(err, r.length, 4, prefix, (const uint32_t*)r.d());
            fmt_num(err, r.length, 7, prefix, (const float*)r.d());
            break;
        case TestSuite::TYPE_FLOAT64:
            fmt_hex(err, r.length, 8, prefix, (const uint64_t*)r.d());
            fmt_num(err, r.length, 17, prefix, (const double*)r.d());
            break;
        }
    };

    auto cmpeq_result = [](const TestSuite::Result& ia, const TestSuite::Result& ib,
                           unsigned fp_prec, unsigned fp_zero_eq) -> bool
    {
        if (std::memcmp(ia.d(), ib.d(), ia.el_size * ia.length) == 0) {
            return true;
        }

        switch (ia.type) {
        case TestSuite::TYPE_FLOAT32:
            return cmpeq_arrays((const float*)ia.d(), (const float*)ib.d(), ia.length,
                                fp_prec, fp_zero_eq);
        case TestSuite::TYPE_FLOAT64:
            return cmpeq_arrays((const double*)ia.d(), (const double*)ib.d(), ia.length,
                                fp_prec, fp_zero_eq);
        default:
            return false;
        }
    };

    // Handle fatal errors first
    if (std::strcmp(a.name_, b.name_) != 0) {
        fmt_separator();
        fmt_file();
        err << "FATAL: Test case names do not match: \""
            << a.name_ << "\" and \""  << b.name_ << "\"\n";
        fmt_separator();
        return false;
    }

    if (a.results_.size() != b.results_.size()) {
        if (a.results_.size() == 0 || b.results_.size() == 0) {
            return true; // Ignore empty result sets
        }
        fmt_separator();
        fmt_file();
        fmt_test_case();
        err << "FATAL: The number of result sections do not match: "
            << a.results_.size() << "/" << b.results_.size() << "\n";
        fmt_separator();
        return false;
    }

    bool ok = true;
    // Compare results
    for (unsigned is = 0; is < a.results_.size(); is++) {
        const auto& sect_a = a.results_[is];
        const auto& sect_b = b.results_[is];

        if (sect_a.empty() || sect_b.empty())
            continue;

        if (sect_a.size() != sect_b.size()) {
            fmt_separator();
            fmt_file();
            fmt_test_case();
            err << "FATAL: The number of results in a section do not match: "
                << " section: " << is << " result count: "
                << sect_a.size() << "/" << sect_b.size() << "\n";
            fmt_separator();
            return false;
        }

        for (unsigned i = 0; i < sect_a.size(); ++i) {
            const auto& ia = sect_a[i];
            const auto& ib = sect_b[i];

            if (ia.line != ib.line) {
                fmt_separator();
                fmt_file();
                fmt_test_case();
                err << "FATAL: Line numbers do not match for items with the same "
                    << "sequence number: section: " << is << " id: " << i
                    << " line_A: " << ia.line << " line_B: " << ib.line << "\n";
                fmt_separator();
                return false;
            }

            if (ia.type != ib.type) {
                fmt_separator();
                fmt_file_line(ia.line);
                fmt_test_case();
                err << "FATAL: Types do not match for items with the same "
                    << "sequence number: id: " << i
                    << " type_A: " << type_str(ia.type)
                    << " line_B: " << type_str(ib.type) << "\n";
                fmt_separator();
                return false;
            }

            unsigned prec = std::max(TestSuite::precision_for_result(ia),
                                     TestSuite::precision_for_result(ib));

            bool fp_zero_eq = ia.fp_zero_eq || ib.fp_zero_eq;

            if (!cmpeq_result(ia, ib, prec, fp_zero_eq)) {
                fmt_separator();
                fmt_file_line(ia.line);
                fmt_test_case();
                fmt_seq(ia.seq);
                err << "ERROR: Vectors not equal: \n";
                fmt_vector(ia, "A : ");
                fmt_vector(ib, "B : ");
                fmt_prec(prec);
                fmt_separator();
                ok = false;
            }
        }
    }
    return ok;
}
