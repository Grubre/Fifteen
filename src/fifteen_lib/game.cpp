#include "game.hpp"
#include <optional>
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

auto find_solution(fifteen start, fifteen_board goal, std::function<int(const fifteen_board)> heuristic) -> std::optional<solution> {
    const auto inf = std::numeric_limits<int>::max();

    uint64_t opened_nodes_cnt = 0;

    if(!(start.board().is_valid() && start.board().is_solvable())) {
        return std::nullopt;
    }

    auto distance = std::unordered_map<fifteen, int>{};
    auto heuristic_eval = std::unordered_map<fifteen, int>{};

    // A star
    auto fifteen_comparator = [&](fifteen l, fifteen r) {
        return distance[l] + heuristic_eval[l.board()] > distance[r] + heuristic_eval[r.board()];
        // return heuristic(l.board()) > heuristic(r.board());
    };

    auto openSet = std::priority_queue<fifteen, std::vector<fifteen>, decltype(fifteen_comparator)>{fifteen_comparator};
    auto isInOpenSet = std::unordered_map<fifteen, bool>{};

    auto push_to_open_set = [&](fifteen a) {
        openSet.push(a);
        isInOpenSet[a] = true;
    };
    auto remove_from_open_set = [&](fifteen a) {
        openSet.pop();
        isInOpenSet[a] = false;
    };

    push_to_open_set(start);

    auto cameFrom = std::map<fifteen, fifteen>{};

    distance[start] = 0;

    heuristic_eval[start] = heuristic(start.board());

    cameFrom[start] = fifteen{};

    while(!openSet.empty()) {
        auto current = openSet.top();
        opened_nodes_cnt++;
        if(current.board() == goal) {
            // std::cout << "Reconstructing path..." << std::endl;
            auto path = reconstruct_path(cameFrom, current);
            std::ranges::reverse(path);
            return solution{.path = path, .opened_nodes_cnt = opened_nodes_cnt};
        }

        remove_from_open_set(current);

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
                    push_to_open_set(neighbour);
                }
            }
        }
    }

    return {};
}

