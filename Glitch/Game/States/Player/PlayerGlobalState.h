#pragma once
#include "Game/States/IState.h"

class Player;

/// @brief Class for the global player state
class PlayerGlobalState : public IState<Player>
{
public:
    virtual ~PlayerGlobalState() {}

    void entry(Player& entity) override;
    void execute(Player& entity) override;
    void exit(Player& entity) override;
};