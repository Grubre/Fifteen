#include "game.hpp"

auto game::start() -> void {
    m_board = fifteen::get_random();
    for(int i = 0; i < 16; i++) {
        if(m_board.get(i) == 0) {
            zero_position = i;
            break;
        }
    }
}

auto game::is_finished() const -> bool {
    return m_board.is_solved();
}

static std::vector<move> possible_moves_lookup[16];
auto game::initialize_lookup() -> void {
    for(uint8_t i = 0; i < 16; i++) {
        if(i % 4 != 0) { // if it is not one of the leftmost tiles
            possible_moves_lookup[i].push_back({static_cast<uint8_t>(i - 1), i});
        }
        if(i % 4 != 3) { // if it is not one of the rightmost tiles
            possible_moves_lookup[i].push_back({static_cast<uint8_t>(i + 1), i});
        }
        if(i > 3) { // if it is not in the first row
            possible_moves_lookup[i].push_back({static_cast<uint8_t>(i - 4), i});
        }
        if(i < 12) { // if it is not in the last row
            possible_moves_lookup[i].push_back({static_cast<uint8_t>(i + 4), i});
        }
    }
}

auto game::possible_moves() const -> const std::vector<move>& {
    return possible_moves_lookup[zero_position];
}

auto game::make_move(move m) -> void {
    m_board.swap(m.index1, m.index2);
    zero_position = m.index1;
}

auto game::make_move_and_print(move m) -> void {
    make_move(m);
    m_board.print();
}

auto game::board() -> fifteen& {
    return m_board;
}

