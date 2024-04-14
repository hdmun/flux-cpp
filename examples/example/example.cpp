#include <iostream>
#include <string>
#include <cstdint>

#include "flux.hpp"
#include "player.h"

int main()
{
    Player player1;
    player1.Init();

    player1.battle.Damage(10);
    player1.info.LevelUp();
    player1.Update();

    Player player2;
    player2.Init();

    player2.battle.Damage(10'000);
    player2.Update();

    return 0;
}
