#include "player.h"
#include "player_info.h"
#include "player_battle.h"

std::int32_t g_id = 0;

Player::Player()
    : id(++g_id)
    , info(this)
    , battle(this)
{
}

void Player::Init()
{
    info.Init();
    battle.Init();
}

void Player::Update()
{
    dispatcher.DispatchAll();
}