#pragma once
#include "checked_fifteen.hpp"
#include <vector>
#include <array>
#include <optional>
#include <functional>

auto find_solution(checked_fifteen start, fifteen goal, std::function<int(const fifteen)> heuristic) -> std::optional<std::vector<checked_fifteen>>;
