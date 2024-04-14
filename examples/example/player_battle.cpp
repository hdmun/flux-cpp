#include "player_battle.h"
#include "player.h"

PlayerBattle::PlayerBattle(Player* player)
    : player(player)
    , hp(10'000)
{
}


void PlayerBattle::Init()
{
    player->dispatcher.Listen<ActPlayerDamaged>(std::bind(&PlayerBattle::OnDamaged, this, std::placeholders::_1));
    player->dispatcher.Listen<ActPlayerLevelChanged>(std::bind(&PlayerBattle::OnLevelChanged, this, std::placeholders::_1));
}

void PlayerBattle::Damage(std::int64_t damage)
{
    auto hpPrev = hp;

    hp -= damage;

    auto action = std::make_shared<ActPlayerDamaged>();
    action->damage = damage;
    action->prevHp = hpPrev;
    player->dispatcher.Fire(std::move(action));
}

void PlayerBattle::OnDamaged(ActPlayerDamaged* action)
{
    std::cout << __FUNCTION__ << ": playerId-" << player->id << ", hp: " << player->battle.hp << std::endl;
}

void PlayerBattle::OnLevelChanged(ActPlayerLevelChanged* action)
{
    std::cout << __FUNCTION__ << ": playerId-" << player->id << ", hp: " << hp << std::endl;
    hp = 10'000;
}