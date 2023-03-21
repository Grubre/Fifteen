#include "checked_fifteen.hpp"

checked_fifteen::checked_fifteen() {
    initialize_lookup();
}

checked_fifteen::checked_fifteen(fifteen f) : checked_fifteen::checked_fifteen() {
    m_board = f;
    zero_position = find_empty_tile_index();
}

auto checked_fifteen::get_random() -> checked_fifteen {
    auto f = checked_fifteen{fifteen::get_random()};
    f.zero_position = f.find_empty_tile_index();
    return f;
}

auto checked_fifteen::is_solved() const -> bool {
    return m_board.is_solved();
}

static auto possible_moves_lookup = std::array<std::vector<move>, 16>{};
static volatile bool lookup_filled = false;

auto checked_fifteen::initialize_lookup() -> void {
    if(lookup_filled) {
        return;
    }

    for(index_type i = 0; i < 16; i++) {
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
    lookup_filled = true;
}

auto checked_fifteen::get_move_lookup() -> const std::array<std::vector<move>, 16>& {
    return possible_moves_lookup;
}

auto checked_fifteen::possible_moves() const -> const std::vector<move>& {
    return possible_moves_lookup[zero_position];
}

auto checked_fifteen::make_move(move m) -> void {
    m_board.swap(m.index1, m.index2);
    zero_position = m.index1;
}

auto checked_fifteen::find_empty_tile_index() -> index_type {
    for(auto i = 0; i < 16; i++) {
        if(m_board.get(i) == 0) {
            return i;
        }
    }
    return -1;
}

auto checked_fifteen::board() -> fifteen& {
    return m_board;
}
auto checked_fifteen::board() const -> const fifteen& {
    return m_board;
}
