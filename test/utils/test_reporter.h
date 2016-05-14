/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TEST_UTILS_TEST_REPORTER_H
#define LIBSIMDPP_TEST_TEST_UTILS_TEST_REPORTER_H

#include <iostream>

/// Stores the summary of the tests that have been run so far (the number of
/// successful and failed test cases). Also, stores a reference to output
/// stream where the actual test results should be reported.
class TestReporter {
public:
    TestReporter(std::ostream& str) :
        num_failure_(0), num_success_(0), output_(str) {}

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

    std::ostream& out() { return output_; }

    void report_summary()
    {
        output_ << "Test summary:\n"
                << "Number of tests:  " << num_success() + num_failure() << "\n"
                << "Successful tests: " << num_success() << "\n"
                << "Failed tests:     " << num_failure() << "\n";
    }

private:
    unsigned num_failure_;
    unsigned num_success_;
    std::ostream& output_;
};


#endif
