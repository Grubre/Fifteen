#include "fifteen_board.hpp"
#include <gtest/gtest.h>

TEST(fifteen_test, default_constructor_test) {
    auto f = fifteen_board{};
    ASSERT_EQ(f.state, 0x0);
}

TEST(fifteen_test, state_type_constructor_test) {
    auto val = 0x2854738201347349;
    auto f = fifteen_board(val);
    ASSERT_EQ(f.state, val);
}

TEST(fifteen_test, get_test) {
    auto f = fifteen_board(0xFEDCBA9876543210); 
    for(int i = 0; i < 16; i++) {
        ASSERT_EQ(f.get(i), 15 - i);
    }
}

TEST(fifteen_test, set_test) {
    auto f = fifteen_board{}; 
    auto numbers = std::vector<int>{0xF,0xE,0xD,0xC,0xB,0xA,9,8,7,6,5,4,3,2,1,0};
    for(int i = 0; i < 16; i++) {
        f.set(i, numbers[i]);
    }
    for(int i = 0; i < 16; i++) {
        ASSERT_EQ(f.get(i), numbers[i]);
    }
}

TEST(fifteen_test, swap_test) {
    auto f = fifteen_board(0x123456789ABCDEF0);
    for(auto i = 0; i < 15; i++) {
        auto a = f.get(i);
        auto b = f.get(i + 1);
        f.swap(i, i+1);
        ASSERT_EQ(f.get(i + 1), a);
        ASSERT_EQ(f.get(i), b);
    }
}

TEST(fifteen_test, get_solved_test) {
    auto f = fifteen_board::get_solved();
    ASSERT_EQ(f.state, 0x123456789ABCDEF0);
    for(int i = 0; i < 16; i++) {
        ASSERT_EQ(f.get(i), (i + 1) % 16);
    }
}

TEST(fifteen_test, correctly_placed_test) {
    auto f = fifteen_board::get_solved();
    ASSERT_EQ(f.correctly_placed(), 16);
    auto a = fifteen_board{};
    for(int i = 0; i < 15; i++) {
        a.set(i, i + 1);
        ASSERT_EQ(a.correctly_placed(), i + 2);
    }
}

TEST(fifteen_test, misplaced_test) {
    auto f = fifteen_board::get_solved();
    ASSERT_EQ(f.misplaced(), 0);
    auto a = fifteen_board{};
    for(int i = 0; i < 15; i++) {
        a.set(i, i + 1);
            ASSERT_EQ(a.misplaced(), 14 - i);
    }
}

TEST(fifteen_test, is_solved_test) {
    auto f = fifteen_board{};
    ASSERT_FALSE(f.is_solved());
    auto a = fifteen_board::get_solved();
    ASSERT_TRUE(a.is_solved());
    auto b = fifteen_board{fifteen_board::correct_placement};
    ASSERT_TRUE(b.is_solved());
    auto c = fifteen_board{0x123456789ABCDEF0};
    ASSERT_TRUE(c.is_solved());
}

TEST(fifteen_test, is_valid_test) {
    auto f = fifteen_board{};
    ASSERT_FALSE(f.is_valid());
    auto a = fifteen_board::get_solved();
    ASSERT_TRUE(a.is_valid());
    for(int i = 0; i < 100; i++) {
        auto b = fifteen_board::get_random();
        ASSERT_TRUE(b.is_valid());
    }
}

TEST(fifteen_test, equals_test) {
    auto a = fifteen_board{};
    auto b = a;
    ASSERT_EQ(a, b);
    ASSERT_EQ(b, a);
    a = fifteen_board::get_random();
    b = a;
    ASSERT_EQ(a, b);
    ASSERT_EQ(b, a);
    a = fifteen_board::get_solved();
    b = a;
    ASSERT_EQ(a, b);
    ASSERT_EQ(b, a);
}

TEST(fifteen_test, not_equals_test) {
    auto a = fifteen_board{0x1};
    auto b = fifteen_board{0x2};
    ASSERT_NE(a, b);
    ASSERT_NE(b, a);
}
