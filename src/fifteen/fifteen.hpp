#pragma once
#include <cstdint>
#include <cstdlib>
#include <random>
#include <vector>
#include <algorithm>
#include <cstdio>

struct fifteen {
    using state_mask = uint64_t;

    fifteen() = default;
    fifteen(state_mask state);

    auto set(uint8_t index, uint64_t value) -> void;
    auto get(uint8_t index) const -> uint8_t;
    auto correctly_placed() const -> uint8_t;
    auto misplaced() const -> uint8_t;
    auto is_solved() const -> bool;
    auto swap(uint8_t index1, uint8_t index2) -> void;

    state_mask state;
    static constexpr uint64_t msb_64bit_mask = 0xF000000000000000;
    static constexpr uint64_t correct_placement = 0x123456789ABCDEF0;

    auto static get_random() -> fifteen;
    auto static get_correct() -> fifteen;

    auto operator==(const fifteen& other) const -> bool;
    auto operator!=(const fifteen& other) const -> bool;

    auto print() const -> void;
};
