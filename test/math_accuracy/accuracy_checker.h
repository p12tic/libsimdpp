/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef SIMDPP_TEST_MATH_ACCURACY_ACCURACY_TRACKER_H
#define SIMDPP_TEST_MATH_ACCURACY_ACCURACY_TRACKER_H

#include <simdpp/core/aligned_allocator.h>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

inline float fast_next_value_to_inf(float a)
{
    int a_int = 0;
    std::memcpy(&a_int, &a, sizeof(a));
    a_int++;
    std::memcpy(&a, &a_int, sizeof(a));
    return a;
}

template<class T>
class AccuracyChecker {
public:
    void set_scratchpad_size(std::size_t size)
    {
        scratchpad_size_ = size;
    }

    void set_bounds(const std::vector<std::pair<T, T>>& bounds)
    {
        bounds_ = bounds;
    }

    template<class FExpected, class FCheck>
    void run_check(FExpected&& expected_cb, FCheck&& check_cb)
    {
        source_scratchpad_.resize(scratchpad_size_);
        dest_expected_scratchpad_.resize(scratchpad_size_);
        dest_check_scratchpad_.resize(scratchpad_size_);

        if (bounds_.empty()) {
            return;
        }

        std::size_t curr_bounds_i = 0;
        T curr_value = bounds_.front().first;
        T target_value = bounds_.front().second;

        while (true) {
            std::size_t scratchpad_valid_size = 0;

            for (std::uint32_t i = 0; i < scratchpad_size_; ++i) {

                source_scratchpad_[i] = curr_value;
                scratchpad_valid_size = i;

                if (std::memcmp(&curr_value, &target_value, sizeof(curr_value)) == 0) {
                    curr_bounds_i++;
                    if (curr_bounds_i == bounds_.size()) {
                        break;
                    }

                    curr_value = bounds_[curr_bounds_i].first;
                    target_value = bounds_[curr_bounds_i].second;
                } else {
                    curr_value = fast_next_value_to_inf(curr_value);
                }
            }
            scratchpad_valid_size++;

            // ensure that the amount of data aligns with SIMD vector sizes
            while (scratchpad_valid_size % 32 != 0) {
                source_scratchpad_[scratchpad_valid_size] =
                    source_scratchpad_[scratchpad_valid_size - 1];
                scratchpad_valid_size++;
            }

            #pragma omp parallel
            {
                #pragma omp single nowait
                expected_cb(source_scratchpad_.data(), dest_expected_scratchpad_.data(),
                            scratchpad_valid_size);

                #pragma omp single nowait
                check_cb(source_scratchpad_.data(), dest_check_scratchpad_.data(),
                         scratchpad_valid_size);
            }

            submit_scratchpads(scratchpad_valid_size);

            if (curr_bounds_i == bounds_.size()) {
                break;
            }
        }
    }

    void describe(const std::string& name)
    {
        std::cout << "Check " << name
                  << ": abs diff " << max_abs_diff_ << " at " << max_abs_at_
                  << " rel diff " << max_rel_diff_ << " at " << max_rel_at_ << "\n";
    }
private:

    void submit_scratchpads(std::size_t size)
    {
        for (std::size_t i = 0; i < size; ++i) {
            T expected = dest_expected_scratchpad_[i];
            T result = dest_check_scratchpad_[i];
            T input = source_scratchpad_[i];

            T abs_diff = std::fabs(expected - result);
            T rel_diff = std::fabs((expected - result) / expected);

            if (abs_diff > max_abs_diff_) {
                max_abs_diff_ = abs_diff;
                max_abs_at_ = input;
            }
            if (rel_diff > max_rel_diff_) {
                max_rel_diff_ = rel_diff;
                max_rel_at_ = input;
            }
        }
    }

    std::size_t scratchpad_size_ = 128 * 1024 * 1024;
    T max_rel_at_ = 0;
    T max_rel_diff_ = 0;
    T max_abs_at_ = 0;
    T max_abs_diff_ = 0;
    std::vector<std::pair<T, T>> bounds_;
    std::vector<T, simdpp::aligned_allocator<T, sizeof(T)>> source_scratchpad_;
    std::vector<T, simdpp::aligned_allocator<T, sizeof(T)>> dest_expected_scratchpad_;
    std::vector<T, simdpp::aligned_allocator<T, sizeof(T)>> dest_check_scratchpad_;
};

#endif
