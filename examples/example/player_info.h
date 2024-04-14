#pragma once
#include "actions.h"

class Player;
class PlayerInfo
{
public:
    PlayerInfo(Player* player);
    virtual ~PlayerInfo() {}

    void Init();
    void LevelUp();

    Player* player;
    std::int32_t level;

    void OnDamaged(ActPlayerDamaged* action);
    void OnDead(ActPlayerDead* action);
};
