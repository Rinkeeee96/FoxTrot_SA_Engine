#pragma once
#include "Game/States/IGlobalState.h"

class Player;

/// @brief Class for the global player state
class PlayerGlobalState : public IGlobalState<Player>
{
private:
    int health;
public:
    void execute(Player* entity) override;
};