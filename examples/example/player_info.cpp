#include "player_info.h"
#include "player.h"

PlayerInfo::PlayerInfo(Player* player)
    : player(player)
    , level(1)
{
}

void PlayerInfo::Init()
{
    player->dispatcher.Listen<ActPlayerDamaged>(std::bind(&PlayerInfo::OnDamaged, this, std::placeholders::_1));
    player->dispatcher.Listen<ActPlayerDead>(std::bind(&PlayerInfo::OnDead, this, std::placeholders::_1));
}

void PlayerInfo::LevelUp()
{
    auto prevLevel = level;
    level++;

    auto action = std::make_shared<ActPlayerLevelChanged>();
    action->level = level;
    action->prevLevel = prevLevel;
    player->dispatcher.Fire(std::move(action));
}

void PlayerInfo::OnDamaged(ActPlayerDamaged* action)
{
    std::cout << __FUNCTION__ << ": playerId-" << player->id << ", hp: " << player->battle.hp << std::endl;
}

void PlayerInfo::OnDead(ActPlayerDead* action)
{
    std::cout << __FUNCTION__ << ": playerId-" << player->id << ", hp: " << player->battle.hp << std::endl;
}