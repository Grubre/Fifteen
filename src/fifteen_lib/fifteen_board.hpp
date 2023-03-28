#pragma once
#include <array>
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <random>
#include <vector>
#include <algorithm>
#include <cstdio>

struct fifteen_board {
    using state_type = uint64_t;
    using index_type = uint8_t;
    using value_type = uint8_t;

    constexpr fifteen_board() = default;
    constexpr fifteen_board(state_type state);

    auto constexpr get(index_type index) const -> value_type;
    auto constexpr set(index_type index, state_type value) -> void;
    auto constexpr swap(index_type index1, index_type index2) -> void;

    auto constexpr correctly_placed() const -> index_type;
    auto constexpr misplaced() const -> index_type;
    auto constexpr is_solved() const -> bool;
    auto constexpr is_valid() const -> bool;
    auto constexpr is_solvable() const -> bool;

    auto constexpr inversions() const -> uint32_t;

    auto constexpr operator==(const fifteen_board& other) const -> bool;
    auto constexpr operator!=(const fifteen_board& other) const -> bool;

    auto print() const -> void;

    auto static get_random() -> fifteen_board;
    auto static constexpr get_solved() -> fifteen_board;

    static constexpr state_type msb_64bit_mask = 0xF000000000000000;
    static constexpr state_type correct_placement = 0x123456789ABCDEF0;

    state_type state;
};

constexpr fifteen_board::fifteen_board(state_type state) : state(state) {}

auto constexpr fifteen_board::set(index_type index, state_type value) -> void {
    state_type offset = index << 2;
    state_type mask = ~(msb_64bit_mask >> offset);
    state = (state & mask) | (value << (60 - offset));
}

auto constexpr fifteen_board::get(index_type index) const -> value_type {
    index_type offset = index << 2;
    return (state & (msb_64bit_mask >> offset)) >> (60 - offset);
}

auto constexpr fifteen_board::correctly_placed() const -> index_type {
    state_type in_place = state & correct_placement;
    index_type cnt = 0;
    state_type mask = msb_64bit_mask;
    for(int i = 0; i < 15; i++) {
        cnt += ((in_place & mask) != 0);
        mask >>= 4;
    }
    cnt += ((in_place & 0xF) == 0);
    return cnt;
}

auto constexpr fifteen_board::misplaced() const -> index_type {
    return 16 - correctly_placed();
}


auto constexpr fifteen_board::is_solved() const -> bool {
    return state == correct_placement;
}

auto constexpr fifteen_board::is_valid() const -> bool {
    auto values_present = std::array<value_type, 16>{};
    for(auto i = 0; i < 16; i++) {
        auto value = get(i);
        if(value > 15) {
            return false;
        }
        values_present[value]++;
        if(values_present[value] > 1) {
            return false;
        }
    }
    return true;
}

inline constexpr auto fifteen_board::is_solvable() const -> bool {
    auto inversion_cnt = inversions();    // std::cout << "inversion_cnt = " << inversion_cnt << std::endl;
    auto zero_pos = 0;
    for(auto i = 0; i < 16; i++) {
        if(get(i) == 0) {
            zero_pos = i / 4;
            break;
        }
    }
    // std::cout << "zero_pos = " << zero_pos << std::endl;
    if (zero_pos & 1)
        return !(inversion_cnt & 1);
    else
        return inversion_cnt & 1;
}

auto constexpr fifteen_board::swap(index_type index1, index_type index2) -> void {
    auto val2 = get(index1);
    set(index1, get(index2));
    set(index2, val2);
}

inline auto fifteen_board::get_random() -> fifteen_board {
    auto a = fifteen_board{};
    auto numbers = std::vector<int>{1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xF};
    auto rd = std::random_device{};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(numbers), std::end(numbers), rng);
    for(int i = 0; i < 16; i++) {
        a.set(i, numbers[i]);
    }
    return a;
}

auto constexpr fifteen_board::get_solved() -> fifteen_board {
    return fifteen_board(correct_placement);
}

auto constexpr fifteen_board::operator==(const fifteen_board& other) const -> bool {
    return state == other.state;
}

auto constexpr fifteen_board::operator!=(const fifteen_board& other) const -> bool {
    return !(*this == other);
}

inline auto fifteen_board::print() const -> void {
    for(auto i = 0; i <= 3; i++) {
        std::printf("[%2d][%2d][%2d][%2d]\n", get(4 * i), get(4 * i + 1), get(4 * i + 2), get(4 * i + 3));
    }
}

auto constexpr fifteen_board::inversions() const -> uint32_t {
    auto inversion_cnt = 0;
    for(auto i = 0; i < 15; i++) {
        for(auto j = i + 1; j < 16; j++) {
            if(get(i) != 0 && get(j) != 0 && get(i) > get(j)) {
                inversion_cnt++;
            }
        }
    }
    return inversion_cnt;
}
