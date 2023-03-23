#include "game.hpp"
#include <queue>
#include <map>
#include <limits>
#include <algorithm>

using move_sequence = fifteen::move_sequence;

auto reconstruct_path(std::map<fifteen, fifteen>& cameFrom, fifteen current) -> std::vector<fifteen> {
    auto total_path = std::vector<fifteen>{};
    total_path.reserve(80);
    while(cameFrom.contains(current)) {
        auto next = cameFrom.at(current);
        cameFrom.erase(current);
        total_path.push_back(current);
        current = next;
    }
    return total_path;
}

auto find_solution(fifteen start, fifteen_board goal, std::function<int(const fifteen_board)> heuristic) -> std::optional<std::vector<fifteen>> {
    auto inf = std::numeric_limits<int>::max();
    if(!(start.board().is_valid() && start.board().is_solvable())) {
        return {};
    }

    // A star
    auto fifteen_comparator = [=](fifteen l, fifteen r) {
        return heuristic(l.board()) > heuristic(r.board());
    };
    auto openSet = std::priority_queue<fifteen, std::vector<fifteen>, decltype(fifteen_comparator)>{fifteen_comparator};
    auto isInOpenSet = std::map<fifteen, bool>{};
    openSet.push(start);
    isInOpenSet[start] = true;

    auto cameFrom = std::map<fifteen, fifteen>{};

    auto distance = std::map<fifteen, int>{};
    distance[start] = 0;

    auto heuristic_eval = std::map<fifteen, int>{};
    heuristic_eval[start] = heuristic(start.board());

    cameFrom[start] = fifteen{};
    cameFrom[start] = fifteen{};

    while(!openSet.empty()) {
        auto current = openSet.top();
        if(current.board() == goal) {
            // std::cout << "Reconstructing path..." << std::endl;
            auto path = reconstruct_path(cameFrom, current);
            std::ranges::reverse(path);
            return path;
        }

        openSet.pop();
        isInOpenSet[current] = false;

        for(auto move : current.possible_moves()) {
            auto neighbour = current;
            neighbour.make_move(move);

            auto tentative_score = distance[current] + 1;

            distance.try_emplace(neighbour, inf);
            if(tentative_score < distance[neighbour]) {
                cameFrom[neighbour] = current;
                distance[neighbour] = tentative_score;
                heuristic_eval[neighbour] = tentative_score + heuristic(neighbour.board());
                if(!isInOpenSet[neighbour]) {
                    isInOpenSet[neighbour] = true;
                    openSet.push(neighbour);
                }
            }
        }
    }

    return {};
}

