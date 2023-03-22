#pragma once
#include "fifteen.hpp"
#include <array>
#include <cstdint>

auto manhattan_distance(const fifteen) -> uint32_t;
auto linear_conflict(const fifteen) -> uint32_t;
auto walking_distance(const fifteen) -> uint32_t;
auto misplaced_tile(const fifteen) -> uint32_t;

auto get_md_lookup() -> const std::array<std::array<uint8_t, 16> ,16>;
