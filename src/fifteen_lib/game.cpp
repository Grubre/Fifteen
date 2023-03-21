#include "game.hpp"
#include <queue>

using move_sequence = checked_fifteen::move_sequence;

auto find_solution(checked_fifteen start, std::function<int(const fifteen)> heuristic) -> std::optional<move_sequence> {
    if(!(start.board().is_valid() && start.board().is_solvable())) {
        return {};
    }

    auto finished = checked_fifteen{start.board().get_solved()};

    auto ret = std::optional<move_sequence>{};

    // A star
    auto fifteen_comparator = [=](checked_fifteen l, checked_fifteen r) {
        return heuristic(l.board()) < heuristic(r.board());
    };
    auto openSet = std::priority_queue<checked_fifteen, std::vector<checked_fifteen>, decltype(fifteen_comparator)>{fifteen_comparator};


    return ret;
}

