/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TEST_UTILS_TEST_REPORTER_H
#define LIBSIMDPP_TEST_TEST_UTILS_TEST_REPORTER_H

/// Stores the number of successful and failed test cases.
class TestReporter {
public:
    TestReporter() : num_failure_(0), num_success_(0) {}

    unsigned num_failure() const { return num_failure_; }
    unsigned num_success() const { return num_success_; }

    void add_result(bool success)
    {
        if (success) {
            num_success_++;
        } else {
            num_failure_++;
        }
    }

    bool success() const { return num_failure_ == 0; }

private:
    unsigned num_failure_;
    unsigned num_success_;
};


#endif
