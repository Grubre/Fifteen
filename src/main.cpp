#include <iostream>
#include "fifteen.hpp"
#include "game.hpp"
#include "heuristics.hpp"
#include <array>
#include <algorithm>
#include  <random>
#include  <iterator>

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

auto get_start() -> checked_fifteen {
    auto ret = checked_fifteen{fifteen::get_solved()};
    for(int i = 0; i < 20; i++) {
        // ret.board().print();
        // std::cout << "================" << std::endl;
        ret.make_move(*select_randomly(ret.possible_moves().begin(), ret.possible_moves().end()));
    }
    return ret;
}

auto main() -> int {
    auto start = checked_fifteen::get_random();
    // auto start = get_start();
    start.board().print();
    auto finish = fifteen::get_solved();
    auto x = find_solution(start, finish, manhattan_distance);
    if(x) {
        std::cout << "solution:" << std::endl;
        for(auto i : *x) {
            i.board().print();
            std::cout << "================" << std::endl;
        }
        std::cout << "solution len = " << x->size() << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
    // auto f = fifteen{0x6D7A89B0F2C5E314};
    // auto f = fifteen{0x391FEB46D0AC2785};
    // std::cout << std::boolalpha << f.is_valid() << std::endl;
    // std::cout << std::boolalpha << f.is_solvable() << std::endl;
    return 0;
}
