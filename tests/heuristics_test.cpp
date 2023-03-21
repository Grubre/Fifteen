#include "heuristics.hpp"
#include <gtest/gtest.h>
#include <algorithm>
#include <limits>

TEST(heuristics_test, initialize_md_lookup) {
    auto md_lookup = get_md_lookup();
    for(int8_t i = 0; i < 16; i++) {
        int8_t x1 = i % 4;
        int8_t y1 = i / 4;
        for(int8_t j = 0; j < 16; j++) {
            int8_t x2 = j % 4;
            int8_t y2 = j / 4;
            auto dist = std::abs(x1 - x2) + std::abs(y1 - y2);
            ASSERT_EQ(md_lookup[(i + 1) % 16][j], dist);
        }
    }
}

TEST(heuristics_test, md_lookup_max_min) {
    auto md_lookup = get_md_lookup();
    auto max_val = std::numeric_limits<uint8_t>::min();
    auto min_val = std::numeric_limits<uint8_t>::max();
    for(auto i = 0; i < 16; i++) {
        for(auto j = 0; j < 16; j++) {
            max_val = std::max(max_val, md_lookup[i][j]);
            min_val = std::min(min_val, md_lookup[i][j]);
        }
    }
    ASSERT_EQ(max_val, 6);
    ASSERT_EQ(min_val, 0);
}
