#pragma once
#include "checked_fifteen.hpp"
#include <vector>
#include <array>
#include <optional>
#include <functional>

auto find_solution(std::function<int(fifteen)> heuristic) -> std::optional<checked_fifteen::move_sequence>;
