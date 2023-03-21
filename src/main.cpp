#include <iostream>
#include "fifteen.hpp"
#include "game.hpp"
#include "heuristics.hpp"
#include <array>
#include <algorithm>

auto main() -> int {
    // game::initialize_lookup();
    // game g;
    // g.board() = fifteen::get_solved();
    // g.board().set(0, 15);
    // g.board().set(14, 1);
    // std::cout << (int)manhattan_distance(g.board()) << std::endl;
    auto md_lookup = get_md_lookup();
    // auto max_val = std::max(md_lookup[0].begin(), md_lookup[15].end());
    // std::cout << "max: " << (int)*max_val << std::endl;
    uint8_t max_val = 0;
    
    for(auto i = 0; i < 16; i++) {
        for(auto j = 0; j < 16; j++) {
            max_val = std::max(max_val, md_lookup[i][j]);
            std::cout << (int)md_lookup[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << (int)max_val << std::endl;
    return 0;
}
