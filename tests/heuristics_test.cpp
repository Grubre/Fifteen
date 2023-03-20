#include "heuristics.hpp"
#include <gtest/gtest.h>

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
