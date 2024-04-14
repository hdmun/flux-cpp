#pragma once
#include <cstdint>
#include "flux.hpp"

struct ActPlayerDamaged : fluxcpp::IActionPayload
{
    std::int64_t prevHp;
    std::int64_t damage;
};

struct ActPlayerDead : fluxcpp::IActionPayload
{
};

struct ActPlayerLevelChanged : fluxcpp::IActionPayload
{
    std::int32_t level;
    std::int32_t prevLevel;
};
