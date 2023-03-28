#include "heuristics.hpp"
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
    static constexpr auto S = N;
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

auto get_md_lookup() -> const std::array<std::array<uint8_t, 16> ,16> {
    return md_lookup<>::table;
}

auto manhattan_distance(const fifteen_board board) -> uint32_t {
    uint32_t acc = 0;
    for(uint32_t i = 0; i < 16; i++) {
        acc += md_lookup<>::table[board.get(i)][i];
    }
    return acc;
}

auto linear_conflict(const fifteen_board) -> uint32_t {
    //TODO
}

auto walking_distance(const fifteen_board) -> uint32_t {
    //TODO
}

auto inversion_distance(const fifteen_board f) -> uint32_t {
    return f.inversions();
}

auto misplaced_tile(const fifteen_board f) -> uint32_t {
    return f.misplaced();
}
