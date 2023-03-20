#include "heuristics.hpp"
#include <array>
#include <cstdint>
#include <iostream>
#include <concepts>

template <std::integral T>
static constexpr auto constexpr_abs(T a) -> uint32_t {
    if(a < 0) {
        return -a;
    }
    return a;
}

// populates lookup table[a][b] where a is value at index b
// returns 
template<size_t N = 4>
struct md_lookup {
    static constexpr auto SIZE = N * N;
    static constexpr auto initialize_lookup() -> std::array<std::array<uint8_t, SIZE>, SIZE> {
        std::array<std::array<uint8_t, SIZE> ,SIZE> manhattan;
        for(int8_t i = 0; i < SIZE; i++) {
            int8_t x1 = i % N;
            int8_t y1 = i / N;
            for(int8_t j = 0; j < SIZE; j++) {
                int8_t x2 = j % N;
                int8_t y2 = j / N;
                manhattan[(i + 1) % 16][j] = constexpr_abs(x1 - x2) + constexpr_abs(y1 - y2);
            }
        }
        return manhattan;
    }
    static constexpr std::array<std::array<uint8_t, SIZE> ,SIZE> table{initialize_lookup()};
};

auto manhattan_distance(fifteen board) -> uint32_t {
    uint32_t acc = 0;
    for(uint32_t i = 0; i < 16; i++) {
        acc += md_lookup<>::table[board.get(i)][i];
    }
    return acc;
}

auto linear_conflict(fifteen) -> uint32_t {
    //TODO
}

auto walking_distance(fifteen) -> uint32_t {
    //TODO
}

auto misplaced_tile(fifteen) -> uint32_t {
    //TODO
}
