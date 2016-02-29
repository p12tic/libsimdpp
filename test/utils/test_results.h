/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_UTILS_TEST_RESULTS_H
#define LIBSIMDPP_TEST_UTILS_TEST_RESULTS_H

#include "test_suite.h"
#include <vector>
#include <deque>
#include <functional>
#include <algorithm>

class TestResults {
public:
    // test case container.
    struct TestCaseCont {
        unsigned id; // insertion number. Used for sorting
        TestSuite test_suite;

        TestCaseCont(unsigned i, const TestSuite& t) : id(i), test_suite(t) {}
    };

    TestResults(const char* arch) :
        arch_(arch)
    {
    }

    TestSuite& new_test_suite(const char* name, const char* file)
    {
        unsigned id = test_suites_.size();
        test_suites_.push_back(TestCaseCont(id, TestSuite(name, file)));
        return test_suites_.back().test_suite;
    }

    std::size_t num_results() const
    {
        std::size_t r = 0;
        for (unsigned i = 0; i < test_suites_.size(); ++i) {
            r += test_suites_[i].test_suite.num_results();
        }
        return r;
    }

private:

    friend bool test_equal(const TestResults& a, const TestResults& b,
                           std::ostream& err);

    const char* arch_;
    // use deque because we must never invalidate references to test cases
    std::deque<TestCaseCont> test_suites_;
};

typedef TestResults::TestCaseCont TestCaseCont;
typedef const TestCaseCont* CaseContRef;
typedef std::pair<CaseContRef, CaseContRef> CaseContPair;

inline bool case_cont_cmp(const TestCaseCont* lhs, const TestCaseCont* rhs)
{
    return std::strcmp(lhs->test_suite.name(), rhs->test_suite.name()) < 0;
}

inline bool ins_cmp(const CaseContPair& lhs, const CaseContPair& rhs)
{
    return lhs.first->id < rhs.first->id;
}

inline bool test_equal(const TestResults& a, const TestResults& b, std::ostream& err)
{
    // sort the cases by name
    std::vector<CaseContRef> a_cases;
    for (unsigned i = 0; i < a.test_suites_.size(); ++i) {
        a_cases.push_back(&(a.test_suites_[i]));
    }
    std::vector<CaseContRef> b_cases;
    for (unsigned i = 0; i < b.test_suites_.size(); ++i) {
        b_cases.push_back(&(b.test_suites_[i]));
    }

    std::sort(a_cases.begin(), a_cases.end(), case_cont_cmp);
    std::sort(b_cases.begin(), b_cases.end(), case_cont_cmp);

    std::vector<CaseContPair> to_compare;

    std::vector<CaseContRef>::const_iterator first1 = a_cases.begin();
    std::vector<CaseContRef>::const_iterator last1 = a_cases.end();
    std::vector<CaseContRef>::const_iterator first2 = b_cases.begin();
    std::vector<CaseContRef>::const_iterator last2 = b_cases.end();

    // set intersection. Get test cases present in both result sets
    while (first1 != last1 && first2 != last2) {
        if (case_cont_cmp(*first1, *first2)) {
            ++first1;
        } else  {
            if (!case_cont_cmp(*first2, *first1)) {
                to_compare.push_back(std::make_pair(*first1, *first2));
            }
            ++first2;
        }
    }

    // sort the cases in the order of insertion to the result set
    std::sort(to_compare.begin(), to_compare.end(), ins_cmp);

    // loop through cases with the same names
    bool ok = true;
    for (unsigned i = 0; i < to_compare.size(); ++i) {
        const CaseContPair& io = to_compare[i];
        bool r = test_equal(io.first->test_suite, a.arch_,
                            io.second->test_suite, b.arch_, err);
        if (!r) {
            ok = false;
        }
    }
    return ok;
}

#endif
