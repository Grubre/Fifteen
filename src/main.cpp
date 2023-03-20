#include <iostream>
#include "fifteen.hpp"
#include "game.hpp"
#include "heuristics.hpp"
#include <array>
#include <algorithm>

auto main() -> int {
    game::initialize_lookup();
    game g;
    g.board() = fifteen::get_correct();
    g.board().set(0, 15);
    g.board().set(14, 1);
    std::cout << (int)manhattan_distance(g.board()) << std::endl;
    return 0;
}
