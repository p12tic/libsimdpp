/*  libsimdpp
    Copyright (C) 2012  p12 tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "test_case.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <type_traits>
#include <typeinfo>
#include <cstdlib>

TestCase::TestCase(const char* name, const char* file) :
    name_{name},
    file_{file},
    curr_precision_ulp_{0}
{
    reset_seq();
}

void TestCase::push(Type type, void* data, unsigned line)
{
    results_.emplace_back(type, data, size_for_type(type), line, seq_++,
                          curr_precision_ulp_);
}

std::size_t TestCase::size_for_type(Type t)
{
    switch (t) {
    case TYPE_UINT8x16:
    case TYPE_INT8x16:
    case TYPE_UINT16x8:
    case TYPE_INT16x8:
    case TYPE_UINT32x4:
    case TYPE_INT32x4:
    case TYPE_UINT64x2:
    case TYPE_INT64x2:
    case TYPE_FLOAT32x4:
    case TYPE_FLOAT64x2: return 16;
    case TYPE_UINT8x32:
    case TYPE_INT8x32:
    case TYPE_UINT16x16:
    case TYPE_INT16x16:
    case TYPE_UINT32x8:
    case TYPE_INT32x8:
    case TYPE_UINT64x4:
    case TYPE_INT64x4:
    case TYPE_FLOAT32x8:
    case TYPE_FLOAT64x4: return 32;
    default: std::abort();
    }
}

unsigned TestCase::precision_for_result(const Result& res)
{
    switch (res.type) {
    case TestCase::TYPE_FLOAT32x4:
    case TestCase::TYPE_FLOAT64x2:
    case TestCase::TYPE_FLOAT32x8:
    case TestCase::TYPE_FLOAT64x4:
        return res.prec_ulp;
    default:
        return 0;
    }
}

template<class T> struct fix_char_type { using type = T; };
template<> struct fix_char_type<uint8_t> { using type = int; };
template<> struct fix_char_type<int8_t> { using type = int; };

template<unsigned width, unsigned num_elems, class T>
void fmt_hex(std::ostream& err, const char* prefix, const T* p)
{
    err << prefix << "[ " << std::hex << std::setfill('0');
    err.precision(width);
    for (unsigned i = 0; i < num_elems; i++, p++) {
        // chars need to be converted to some other type
        typename std::make_unsigned<T>::type usg = *p;
        err << std::setw(width*2) << uint64_t(usg);
        if (i != num_elems - 1) {
            err << " ; ";
        }
    }
    err << " ]\n";
    err << std::dec << std::setfill(' ');
}

template<unsigned precision, unsigned num_elems, class T>
void fmt_num(std::ostream& err, const char* prefix, const T* p)
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

template<unsigned num_elems, class T>
bool cmpeq_arrays(const T* a, const T* b, unsigned prec)
{
    for (unsigned i = 0; i < num_elems; i++) {
        // we need to be extra-precise here. nextafter works won't introduce
        // any rounding errors
        T ia = *a++;
        T ib = *b++;
        for (unsigned i = 0; i < prec; i++) {
            ia = std::nextafter(ia, ib);
        }
        if (ia != ib) {
            return false;
        }
    }
    return true;
}

bool test_equal(const TestCase& a, const char* a_arch,
                const TestCase& b, const char* b_arch,
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
        case TestCase::TYPE_UINT8x16: return "uint8x16";
        case TestCase::TYPE_INT8x16: return "int8x16";
        case TestCase::TYPE_UINT16x8: return "uint16x8";
        case TestCase::TYPE_INT16x8: return "int16x8";
        case TestCase::TYPE_UINT32x4: return "uint32x4";
        case TestCase::TYPE_INT32x4: return "int32x4";
        case TestCase::TYPE_UINT64x2: return "uint64x2";
        case TestCase::TYPE_INT64x2: return "int64x2";
        case TestCase::TYPE_FLOAT32x4: return "float32x4";
        case TestCase::TYPE_FLOAT64x2: return "float64x2";
        case TestCase::TYPE_UINT8x32: return "uint8x32";
        case TestCase::TYPE_INT8x32: return "int8x32";
        case TestCase::TYPE_UINT16x16: return "uint16x16";
        case TestCase::TYPE_INT16x16: return "int16x16";
        case TestCase::TYPE_UINT32x8: return "uint32x8";
        case TestCase::TYPE_INT32x8: return "int32x8";
        case TestCase::TYPE_UINT64x4: return "uint64x4";
        case TestCase::TYPE_INT64x4: return "int64x4";
        case TestCase::TYPE_FLOAT32x8: return "float32x8";
        case TestCase::TYPE_FLOAT64x4: return "float64x4";
        default: return "UNDEFINED";
        }
    };
    auto fmt_vector = [&](const TestCase::Result& r, const char* prefix) -> void
    {
        switch (r.type) {
        case TestCase::TYPE_UINT8x16:
            fmt_hex<1,16>(err, prefix, r.u8);
            fmt_num<4,16>(err, prefix, r.u8);
            break;
        case TestCase::TYPE_INT8x16:
            fmt_hex<1,16>(err, prefix, r.s8);
            fmt_num<4,16>(err, prefix, r.s8);
            break;
        case TestCase::TYPE_UINT16x8:
            fmt_hex<2,8>(err, prefix, r.u16);
            fmt_num<6,8>(err, prefix, r.u16);
            break;
        case TestCase::TYPE_INT16x8:
            fmt_hex<2,8>(err, prefix, r.s16);
            fmt_num<6,8>(err, prefix, r.s16);
            break;
        case TestCase::TYPE_UINT32x4:
            fmt_hex<4,4>(err, prefix, r.u32);
            fmt_num<11,4>(err, prefix, r.u32);
            break;
        case TestCase::TYPE_INT32x4:
            fmt_hex<4,4>(err, prefix, r.s32);
            fmt_num<11,4>(err, prefix, r.s32);
            break;
        case TestCase::TYPE_UINT64x2:
            fmt_hex<8,2>(err, prefix, r.u64);
            fmt_num<20,2>(err, prefix, r.u64);
            break;
        case TestCase::TYPE_INT64x2:
            fmt_hex<8,2>(err, prefix, r.s64);
            fmt_num<20,2>(err, prefix, r.s64);
            break;
        case TestCase::TYPE_FLOAT32x4:
            fmt_hex<4,4>(err, prefix, r.u32);
            fmt_num<7,4>(err, prefix, r.f32);
            break;
        case TestCase::TYPE_FLOAT64x2:
            fmt_hex<8,2>(err, prefix, r.u64);
            fmt_num<17,2>(err, prefix, r.f64);
            break;
        // 32-byte vectors
        case TestCase::TYPE_UINT8x32:
            fmt_hex<1,32>(err, prefix, r.u8);
            fmt_num<4,32>(err, prefix, r.u8);
            break;
        case TestCase::TYPE_INT8x32:
            fmt_hex<1,32>(err, prefix, r.s8);
            fmt_num<4,32>(err, prefix, r.s8);
            break;
        case TestCase::TYPE_UINT16x16:
            fmt_hex<2,16>(err, prefix, r.u16);
            fmt_num<6,16>(err, prefix, r.u16);
            break;
        case TestCase::TYPE_INT16x16:
            fmt_hex<2,16>(err, prefix, r.s16);
            fmt_num<6,16>(err, prefix, r.s16);
            break;
        case TestCase::TYPE_UINT32x8:
            fmt_hex<4,8>(err, prefix, r.u32);
            fmt_num<11,8>(err, prefix, r.u32);
            break;
        case TestCase::TYPE_INT32x8:
            fmt_hex<4,8>(err, prefix, r.s32);
            fmt_num<11,8>(err, prefix, r.s32);
            break;
        case TestCase::TYPE_UINT64x4:
            fmt_hex<8,4>(err, prefix, r.u64);
            fmt_num<20,4>(err, prefix, r.u64);
            break;
        case TestCase::TYPE_INT64x4:
            fmt_hex<8,4>(err, prefix, r.s64);
            fmt_num<20,4>(err, prefix, r.s64);
            break;
        case TestCase::TYPE_FLOAT32x8:
            fmt_hex<4,8>(err, prefix, r.u32);
            fmt_num<7,8>(err, prefix, r.f32);
            break;
        case TestCase::TYPE_FLOAT64x4:
            fmt_hex<8,4>(err, prefix, r.u64);
            fmt_num<17,4>(err, prefix, r.f64);
            break;
        }
    };

    auto cmpeq_result = [](const TestCase::Result& ia, const TestCase::Result& ib,
                           unsigned prec) -> bool
    {
        if (std::memcmp(ia.u8, ib.u8, TestCase::size_for_type(ia.type)) == 0) {
            return true;
        }

        if (prec == 0) {
            return false;
        }

        switch (ia.type) {
        case TestCase::TYPE_FLOAT32x4:
            return cmpeq_arrays<4>(ia.f32, ib.f32, prec);
        case TestCase::TYPE_FLOAT64x2:
            return cmpeq_arrays<2>(ia.f64, ib.f64, prec);
        case TestCase::TYPE_FLOAT32x8:
            return cmpeq_arrays<8>(ia.f32, ib.f32, prec);
        case TestCase::TYPE_FLOAT64x4:
            return cmpeq_arrays<4>(ia.f64, ib.f64, prec);
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
        fmt_separator();
        fmt_file();
        fmt_test_case();
        err << "FATAL: The lengths of the result vectors does not match: "
            << a.results_.size() << "/" << b.results_.size() << "\n";
        fmt_separator();
        return false;
    }

    bool ok = true;
    // Compare results
    for (unsigned i = 0; i < a.results_.size(); i++) {
        const auto& ia = a.results_[i];
        const auto& ib = b.results_[i];

        if (ia.line != ib.line) {
            fmt_separator();
            fmt_file();
            fmt_test_case();
            err << "FATAL: Line numbers do not match for items with the same "
                << "sequence number: id: " << i
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

        unsigned prec = std::max(TestCase::precision_for_result(ia),
                                 TestCase::precision_for_result(ib));

        if (!cmpeq_result(ia, ib, prec)) {
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
    return ok;
}
