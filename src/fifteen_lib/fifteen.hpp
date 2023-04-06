#pragma once
#include "fifteen_board.hpp"
#include <vector>
#include <array>
#include <optional>
#include <functional>

struct move {
    uint8_t index1;
    uint8_t index2;
};

class fifteen {
public:
    using index_type = fifteen_board::index_type;
    using move_sequence = std::vector<move>;
public:
    fifteen();
    fifteen(fifteen_board);
public:
    auto possible_moves() const -> const move_sequence&;
    auto board() -> fifteen_board&;
    auto board() const -> const fifteen_board&;
    auto make_move(move) -> void;
    auto find_empty_tile_index() -> index_type;
    auto is_solved() const -> bool;
public:
    auto static initialize_lookup() -> void;
    auto static get_random() -> fifteen;
    auto static get_move_lookup() -> const std::array<std::vector<move>, 16>&;
public:
    auto operator<=>(const fifteen& other) const {
        return (m_board.state <=> other.m_board.state);
    }
    auto operator==(const fifteen& other) const {
        return (m_board.state == other.m_board.state);
    }


private:
    fifteen_board m_board;
    uint8_t zero_position;
};

namespace std {

  template <>
  struct hash<fifteen>
  {
    std::size_t operator()(const fifteen& k) const
    {
      using std::hash;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return hash<uint64_t>()(k.board().state);
    }
  };

}
