#include <iostream>
#include "fifteen.hpp"
#include "game.hpp"
#include "heuristics.hpp"
#include <array>
#include <algorithm>

auto main() -> int {
    auto x = find_solution(checked_fifteen::get_random(), fifteen::get_solved(), manhattan_distance);
    if(x) {
        std::cout << "found" << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
    return 0;
}
