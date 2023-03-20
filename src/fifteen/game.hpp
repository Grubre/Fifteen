#pragma once
#include "fifteen.hpp"
#include <vector>

struct move {
    uint8_t index1;
    uint8_t index2;
};

class game {
public:
    auto start() -> void;
    auto possible_moves() const -> const std::vector<move>&;
    auto is_finished() const -> bool;
    auto board() -> fifteen&;
    auto make_move(move) -> void;
    auto make_move_and_print(move) -> void;
public:
    static auto initialize_lookup() -> void;
private:
    fifteen m_board;
    uint8_t zero_position;
};
