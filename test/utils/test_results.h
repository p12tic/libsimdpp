/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_UTILS_TEST_RESULTS_H
#define LIBSIMDPP_TEST_UTILS_TEST_RESULTS_H

#include "test_results_set.h"
#include "test_reporter.h"
#include <vector>
#include <deque>
#include <functional>
#include <algorithm>

struct TestOptions {
    bool is_simulator;

    TestOptions() : is_simulator(false) {}
};

/** Represents all test results for a particular architecture
*/
class TestResults {
public:
    // test case container.
    struct TestCaseCont {
        unsigned id; // insertion number. Used for sorting
        TestResultsSet results_set;

        TestCaseCont(unsigned i, const TestResultsSet& t) : id(i), results_set(t) {}
    };

    TestResults(const char* arch) :
        arch_(arch)
    {
    }

    TestResultsSet& new_results_set(const char* name)
    {
        unsigned id = (unsigned) test_sets_.size();
        test_sets_.push_back(TestCaseCont(id, TestResultsSet(name)));
        return test_sets_.back().results_set;
    }

private:

    friend void report_test_comparison(const TestResults& a, const TestResults& b,
                                       TestReporter& tr);

    const char* arch_;
    // use deque because we must never invalidate references to test cases
    std::deque<TestCaseCont> test_sets_;
};


typedef TestResults::TestCaseCont TestCaseCont;
typedef const TestCaseCont* CaseContRef;
typedef std::pair<CaseContRef, CaseContRef> CaseContPair;

inline bool case_cont_cmp(const TestCaseCont* lhs, const TestCaseCont* rhs)
{
    return std::strcmp(lhs->results_set.name(), rhs->results_set.name()) < 0;
}

inline bool ins_cmp(const CaseContPair& lhs, const CaseContPair& rhs)
{
    return lhs.first->id < rhs.first->id;
}

inline void report_test_comparison(const TestResults& a, const TestResults& b, TestReporter& tr)
{
    // sort the cases by name
    std::vector<CaseContRef> a_cases;
    for (unsigned i = 0; i < a.test_sets_.size(); ++i) {
        a_cases.push_back(&(a.test_sets_[i]));
    }
    std::vector<CaseContRef> b_cases;
    for (unsigned i = 0; i < b.test_sets_.size(); ++i) {
        b_cases.push_back(&(b.test_sets_[i]));
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
    for (unsigned i = 0; i < to_compare.size(); ++i) {
        const CaseContPair& io = to_compare[i];
        report_test_comparison(io.first->results_set, a.arch_,
                               io.second->results_set, b.arch_, tr);
    }
}

#endif
