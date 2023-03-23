#include "game.hpp"
#include <queue>
#include <map>
#include <limits>
#include <algorithm>

using move_sequence = checked_fifteen::move_sequence;

auto reconstruct_path(std::map<checked_fifteen, checked_fifteen>& cameFrom, checked_fifteen current) -> std::vector<checked_fifteen> {
    auto total_path = std::vector<checked_fifteen>{};
    total_path.reserve(80);
    // total_path.push_back(current);
    // std::cout << "Expanded nodes:" << std::endl;
    // for(auto[key,val] : cameFrom) {
    //     std::cout << "=======================" << std::endl;
    //     std::cout << "current:" << std::endl;
    //     key.board().print();
    //     std::cout << "previous:" << std::endl;
    //     val.board().print();
    //     std::cout << "=======================" << std::endl;
    // }
    while(cameFrom.contains(current)) {
        auto next = cameFrom.at(current);
        cameFrom.erase(current);
        total_path.push_back(current);
        current = next;
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
        return heuristic(l.board()) > heuristic(r.board());
    };
    auto openSet = std::priority_queue<checked_fifteen, std::vector<checked_fifteen>, decltype(fifteen_comparator)>{fifteen_comparator};
    auto isInOpenSet = std::map<checked_fifteen, bool>{};
    openSet.push(start);
    isInOpenSet[start] = true;

    auto cameFrom = std::map<checked_fifteen, checked_fifteen>{};

    auto gScore = std::map<checked_fifteen, int>{};
    gScore[start] = 0;

    auto fScore = std::map<checked_fifteen, int>{};
    fScore[start] = heuristic(start.board());

    cameFrom[start] = checked_fifteen{};
    cameFrom[start] = checked_fifteen{};

    while(!openSet.empty()) {
        auto current = openSet.top();
        // std::cout << "!!!!!current!!!!" << std::endl;
        // current.board().print();
        // std::cout << "!!!!!!!!!!!!!!!!" << std::endl;
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

            auto tentative_score = gScore[current] + 1;

            gScore.try_emplace(neighbour, inf);
            if(tentative_score < gScore[neighbour]) {
                cameFrom[neighbour] = current;
                gScore[neighbour] = tentative_score;
                fScore[neighbour] = tentative_score + heuristic(neighbour.board());
                if(!isInOpenSet[neighbour]) {
                    // std::cout << "====neighbour===" << std::endl;
                    // neighbour.board().print();
                    // std::cout << "================" << std::endl;
                    isInOpenSet[neighbour] = true;
                    openSet.push(neighbour);
                }
            }
        }
    }

    return {};
}

