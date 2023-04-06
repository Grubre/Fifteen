#include <iostream>
#include "fifteen.hpp"
#include "game.hpp"
#include "heuristics.hpp"
#include <array>
#include <algorithm>
#include <random>
#include <iterator>

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

auto get_start() -> fifteen {
    auto ret = fifteen{fifteen_board::get_solved()};
    for(int i = 0; i < 80; i++) {
        // ret.board().print();
        // std::cout << "================" << std::endl;
        ret.make_move(*select_randomly(ret.possible_moves().begin(), ret.possible_moves().end()));
    }
    return ret;
}

auto main() -> int {
    auto start = fifteen::get_random();
    // auto start = fifteen{0x159D26AE37BF48C0};
    // auto start = get_start();

    std::cout << "starting position:" << std::endl;
    start.board().print();
    auto finish = fifteen_board::get_solved();

    if(!start.board().is_valid() || !start.board().is_solvable()) {
        std::cout << "solution cant be found" << std::endl;
        return 0;
    }

    auto manhattan = find_solution(start, finish, manhattan_distance);
    std::cout << "=======================" << std::endl;
    std::cout << "manhattan:" << std::endl;
    manhattan->print_solution();
    // auto id        = find_solution(start, finish, inversion_distance);
    // std::cout << "=======================" << std::endl;
    // std::cout << "inversion distance:" << std::endl;
    // id->print_solution();

    return 0;
}
