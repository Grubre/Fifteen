#pragma once
#include "fifteen.hpp"
#include <cstdint>
#include <vector>
#include <array>
#include <optional>
#include <functional>

struct solution {
    std::vector<fifteen> path;
    uint64_t opened_nodes_cnt;

    void print_solution(bool print_path = false) {
        if(print_path) {
            for(auto i : path) {
                i.board().print();
                std::cout << "================" << std::endl;
            }
        }
        std::cout << "opened nodes = " << opened_nodes_cnt << std::endl;
        std::cout << "path length = " << path.size() << std::endl;
    }
};

auto find_solution(fifteen start, fifteen_board goal, std::function<int(const fifteen_board)> heuristic) -> std::optional<solution>;
