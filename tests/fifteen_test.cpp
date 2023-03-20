#include "fifteen.hpp"
#include <gtest/gtest.h>

TEST(fifteen_test, get_correct_test) {
    auto f = fifteen::get_correct();
    for(int i = 0; i < 16; i++) {
        ASSERT_EQ(f.get(i), (i + 1) % 16);
    }
}
