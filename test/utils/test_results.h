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

struct TestOptions {
    bool is_simulator;

    TestOptions() : is_simulator(false) {}
};

class TestResults {
public:
    // test case container.
    struct TestCaseCont {
        unsigned id; // insertion number. Used for sorting
        TestSuite test_suite;
    };

    TestResults(const char* arch) :
        arch_{arch}
    {
    }

    TestSuite& new_test_suite(const char* name, const char* file)
    {
        unsigned id = test_suites_.size();
        test_suites_.push_back(TestCaseCont{id, TestSuite{name, file}});
        return test_suites_.back().test_suite;
    }

    std::size_t num_results() const
    {
        std::size_t r = 0;
        for (const auto& i: test_suites_) {
            r += i.test_suite.num_results();
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

inline bool test_equal(const TestResults& a, const TestResults& b, std::ostream& err)
{
    using TestCaseCont = TestResults::TestCaseCont;
    using CaseContPair = std::pair<std::reference_wrapper<const TestCaseCont>,
                                   std::reference_wrapper<const TestCaseCont>>;

    using CaseContRef = std::reference_wrapper<const TestCaseCont>;

    auto case_cont_cmp = [](const TestCaseCont& lhs, const TestCaseCont& rhs)
    {
        return std::strcmp(lhs.test_suite.name(), rhs.test_suite.name()) < 0;
    };

    // sort the cases by name
    std::vector<CaseContRef> a_cases(a.test_suites_.begin(), a.test_suites_.end());
    std::vector<CaseContRef> b_cases(b.test_suites_.begin(), b.test_suites_.end());

    std::sort(a_cases.begin(), a_cases.end(), case_cont_cmp);
    std::sort(b_cases.begin(), b_cases.end(), case_cont_cmp);

    std::vector<CaseContPair> to_compare;

    auto first1 = a_cases.begin();
    auto last1 = a_cases.end();
    auto first2 = b_cases.begin();
    auto last2 = b_cases.end();

    // set intersection. Get test cases present in both result sets
    while (first1 != last1 && first2 != last2) {
        if (case_cont_cmp(first1->get(), first2->get())) {
            ++first1;
        } else  {
            if (!case_cont_cmp(first2->get(), first1->get())) {
                to_compare.emplace_back(first1->get(), first2->get());
            }
            ++first2;
        }
    }

    // sort the cases in the order of insertion to the result set
    auto ins_cmp = [](const CaseContPair& lhs, const CaseContPair& rhs)
    {
        return lhs.first.get().id < rhs.first.get().id;
    };
    std::sort(to_compare.begin(), to_compare.end(), ins_cmp);

    // loop through cases with the same names
    bool ok = true;
    for (const auto& io: to_compare) {
        bool r = test_equal(io.first.get().test_suite, a.arch_,
                            io.second.get().test_suite, b.arch_, err);
        if (!r) {
            ok = false;
        }
    }
    return ok;
}

#endif
