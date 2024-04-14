#include <iostream>
#include <string>
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

std::int32_t g_id = 0;

class Player
{
public:
    Player()
        : id(++g_id)
        , level(1)
        , hp(10'000)
    {
    }

    virtual ~Player() {}

    void Init()
    {
        _dispatcher.Listen<ActPlayerDamaged>(std::bind(&Player::OnDamaged, this, std::placeholders::_1));
        // 여러 번 등록 가능
        _dispatcher.Listen<ActPlayerDamaged>(std::bind(&Player::OnDamaged2, this, std::placeholders::_1));

        _dispatcher.Listen<ActPlayerDead>(std::bind(&Player::OnDead, this, std::placeholders::_1));
        _dispatcher.Listen<ActPlayerLevelChanged>(std::bind(&Player::OnLevelChanged, this, std::placeholders::_1));
    }

    void Damage(std::int64_t damage)
    {
        auto hpPrev = hp;

        hp -= damage;

        auto action = std::make_shared<ActPlayerDamaged>();
        action->damage = damage;
        action->prevHp = hpPrev;
        _dispatcher.Fire(std::move(action));
    }

    void LevelUp()
    {
        auto prevLevel = level;
        level++;

        auto action = std::make_shared<ActPlayerLevelChanged>();
        action->level = level;
        action->prevLevel = prevLevel;
        _dispatcher.Fire(std::move(action));
    }

    void Update()
    {
        _dispatcher.DispatchAll();
    }

private:
    void OnDamaged(ActPlayerDamaged* action)
    {
        std::cout << __FUNCTION__ << ": playerId-" << id << std::endl;
    }

    void OnDamaged2(ActPlayerDamaged* action)
    {
        std::cout << __FUNCTION__ << ": playerId-" << id << std::endl;
    }

    void OnDead(ActPlayerDead* action)
    {
        std::cout << __FUNCTION__ << ": playerId-" << id << std::endl;
    }

    void OnLevelChanged(ActPlayerLevelChanged* action)
    {
        std::cout << __FUNCTION__ << ": playerId-" << id << std::endl;
    }

    std::int32_t id;
    std::int64_t hp;
    std::int32_t level;

    fluxcpp::Dispatcher _dispatcher;
};

int main()
{
    Player player1;
    player1.Init();

    player1.Damage(10);
    player1.LevelUp();
    player1.Update();

    Player player2;
    player2.Init();

    player2.Damage(10'000);
    player2.Update();

    return 0;
}
