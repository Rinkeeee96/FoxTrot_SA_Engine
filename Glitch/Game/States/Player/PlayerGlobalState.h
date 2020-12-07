#pragma once
#include "Game/States/IGlobalState.h"

class Player;

class PlayerGlobalState : public IGlobalState<Player>
{
private:
    int health;
public:
    void execute(Player* entity) override;
};