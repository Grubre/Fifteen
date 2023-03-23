#pragma once
#include "fifteen.hpp"
#include <vector>
#include <array>
#include <optional>
#include <functional>

auto find_solution(fifteen start, fifteen_board goal, std::function<int(const fifteen_board)> heuristic) -> std::optional<std::vector<fifteen>>;
