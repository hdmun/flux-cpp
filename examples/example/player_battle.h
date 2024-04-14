#pragma once
#include "actions.h"

class Player;
class PlayerBattle
{
public:
    PlayerBattle(Player* player);
    virtual ~PlayerBattle() {}

    void Init();
    void Damage(std::int64_t damage);

    Player* player;
    std::int64_t hp;

private:
    void OnDamaged(ActPlayerDamaged* action);
    void OnLevelChanged(ActPlayerLevelChanged* action);
};
