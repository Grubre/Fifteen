#include "game.hpp"
#include <queue>
#include <map>
#include <limits>

using move_sequence = checked_fifteen::move_sequence;

auto reconstruct_path(const std::map<checked_fifteen, checked_fifteen>& cameFrom, checked_fifteen current) -> std::vector<checked_fifteen> {
    auto total_path = std::vector<checked_fifteen>{};
    total_path.reserve(80);
    total_path.push_back(current);
    while(cameFrom.contains(current)) {
        current = cameFrom.at(current);
        total_path.push_back(current);
    }
    return total_path;
}

auto find_solution(checked_fifteen start, fifteen goal, std::function<int(const fifteen)> heuristic) -> std::optional<std::vector<checked_fifteen>> {
    auto inf = std::numeric_limits<int>::max();
    if(!(start.board().is_valid() && start.board().is_solvable())) {
        return {};
    }

    // A star
    auto fifteen_comparator = [=](checked_fifteen l, checked_fifteen r) {
        return heuristic(l.board()) < heuristic(r.board());
    };
    auto openSet = std::priority_queue<checked_fifteen, std::vector<checked_fifteen>, decltype(fifteen_comparator)>{fifteen_comparator};
    auto isInOpenSet = std::map<checked_fifteen, bool>{};
    openSet.push(start);
    isInOpenSet[start] = true;

    auto cameFrom = std::map<checked_fifteen, checked_fifteen>{};

    auto gScore = std::map<checked_fifteen, int>{};
    gScore.try_emplace(start.board(), inf);

    auto fScore = std::map<checked_fifteen, int>{};
    fScore.try_emplace(start.board(), heuristic(start.board()));

    while(!openSet.empty()) {
        auto current = openSet.top();
        if(current.board() == goal) {
            return reconstruct_path(cameFrom, current);
        }

        openSet.pop();
        isInOpenSet[current] = false;

        for(auto move : current.possible_moves()) {
            auto neighbour = current;
            neighbour.make_move(move);

            gScore.try_emplace(current, inf);
            auto tentative_score = gScore[current] + 1;

            gScore.try_emplace(neighbour, inf);
            if(tentative_score < gScore[neighbour]) {
                cameFrom[neighbour] = current;
                gScore[neighbour] = tentative_score;
                fScore[neighbour] = tentative_score + heuristic(neighbour.board());
                if(!isInOpenSet[neighbour]) {
                    isInOpenSet[neighbour] = true;
                    openSet.push(neighbour);
                }
            }
        }
    }

    return {};
}

