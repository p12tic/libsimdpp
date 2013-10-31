/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_TEST_TEST_RESULTS_H
#define LIBSIMDPP_TEST_TEST_RESULTS_H

#include "test_case.h"
#include <vector>
#include <deque>
#include <boost/ref.hpp>
#include <algorithm>

class TestResults {
public:
    // test case container.
    struct TestCaseCont {
        unsigned id; // insertion number. Used for sorting
        TestCase test_case;

        TestCaseCont(unsigned i, TestCase tc) : id(i), test_case(tc) {}
    };

    TestResults(const char* arch) :
        arch_(arch)
    {
    }

    TestCase& new_test_case(const char* name, const char* file)
    {
        unsigned id = test_cases_.size();
        test_cases_.push_back(TestCaseCont(id, TestCase(name, file)));
        return test_cases_.back().test_case;
    }

    std::size_t num_results() const
    {
        std::size_t r = 0;
        std::deque<TestCaseCont>::const_iterator it;
        for (it = test_cases_.begin(); it != test_cases_.end(); ++it) {
            r += it->test_case.num_results();
        }
        return r;
    }

private:

    friend bool test_equal(const TestResults& a, const TestResults& b,
                           std::ostream& err);

    const char* arch_;
    // use deque because we must never invalidate references to test cases
    std::deque<TestCaseCont> test_cases_;
};

namespace test_equal_detail {

typedef TestResults::TestCaseCont TestCaseCont;
typedef std::pair<boost::reference_wrapper<const TestCaseCont>,
                  boost::reference_wrapper<const TestCaseCont> > CaseContPair;
typedef boost::reference_wrapper<const TestCaseCont> CaseContRef;

inline bool case_cont_cmp(const TestCaseCont& lhs, const TestCaseCont& rhs)
{
    return std::strcmp(lhs.test_case.name(), rhs.test_case.name()) < 0;
}

inline bool ins_cmp(const CaseContPair& lhs, const CaseContPair& rhs)
{
    return lhs.first.get().id < rhs.first.get().id;
}

} // namespace detail

inline bool test_equal(const TestResults& a, const TestResults& b, std::ostream& err)
{
    using test_equal_detail::TestCaseCont;
    using test_equal_detail::CaseContPair;
    using test_equal_detail::CaseContRef;

    // sort the cases by name
    std::vector<CaseContRef> a_cases(a.test_cases_.begin(), a.test_cases_.end());
    std::vector<CaseContRef> b_cases(b.test_cases_.begin(), b.test_cases_.end());

    std::sort(a_cases.begin(), a_cases.end(), test_equal_detail::case_cont_cmp);
    std::sort(b_cases.begin(), b_cases.end(), test_equal_detail::case_cont_cmp);

    std::vector<CaseContPair> to_compare;

    std::vector<CaseContRef>::iterator first1 = a_cases.begin();
    std::vector<CaseContRef>::iterator last1 = a_cases.end();
    std::vector<CaseContRef>::iterator first2 = b_cases.begin();
    std::vector<CaseContRef>::iterator last2 = b_cases.end();

    // set intersection. Get test cases present in both result sets
    while (first1 != last1 && first2 != last2) {
        if (test_equal_detail::case_cont_cmp(first1->get(), first2->get())) {
            ++first1;
        } else  {
            if (!test_equal_detail::case_cont_cmp(first2->get(), first1->get())) {
                to_compare.push_back(CaseContPair(boost::ref(first1->get()),
                                                  boost::ref(first2->get())));
            }
            ++first2;
        }
    }

    // sort the cases in the order of insertion to the result set
    std::sort(to_compare.begin(), to_compare.end(), test_equal_detail::ins_cmp);

    // loop through cases with the same names
    bool ok = true;
    std::vector<CaseContPair>::iterator it;
    for (it = to_compare.begin(); it != to_compare.end(); ++it) {
        bool r = test_equal(it->first.get().test_case, a.arch_,
                            it->second.get().test_case, b.arch_, err);
        if (!r) {
            ok = false;
        }
    }
    return ok;
}

#endif
