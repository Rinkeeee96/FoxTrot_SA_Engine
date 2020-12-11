#pragma once
#include "Game/States/IState.h"

class Player;

/// @brief 
/// God state of player
class GodState : public IState<Player>
{
public:
    virtual ~GodState() {}

    void entry(Player* entity) override;
    void execute(Player* entity) override;
    void exit(Player* entity) override;

private:

};