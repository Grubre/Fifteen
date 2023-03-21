#pragma once
#include "fifteen.hpp"
#include <vector>
#include <array>
#include <optional>
#include <functional>

struct move {
    uint8_t index1;
    uint8_t index2;
};

class checked_fifteen {
public:
    using index_type = fifteen::index_type;
    using move_sequence = std::vector<move>;
public:
    checked_fifteen();
    checked_fifteen(fifteen);
public:
    auto possible_moves() const -> const move_sequence&;
    auto board() -> fifteen&;
    auto board() const -> const fifteen&;
    auto make_move(move) -> void;
    auto find_empty_tile_index() -> index_type;
    auto is_solved() const -> bool;
public:
    auto static initialize_lookup() -> void;
    auto static get_random() -> checked_fifteen;
    auto static get_move_lookup() -> const std::array<std::vector<move>, 16>&;

private:
    fifteen m_board;
    uint8_t zero_position;
};
