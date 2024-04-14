#pragma once
#include <cstdint>

#include "player_info.h"
#include "player_battle.h"

extern std::int32_t g_id;

class Player
{
public:
    Player();
    virtual ~Player() {}

    void Init();
    void Update();

    std::int32_t id;
    fluxcpp::Dispatcher dispatcher;

    PlayerInfo info;
    PlayerBattle battle;
};
