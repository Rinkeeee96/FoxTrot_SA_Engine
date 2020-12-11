#pragma once
#include "Game/States/IState.h"
#include <chrono>

class Player;

/// @brief 
/// Default state of a player
class NormalState : public IState<Player>
{
public:
    virtual ~NormalState() {}

    void entry(Player* entity) override;
    void execute(Player* entity) override;
    void exit(Player* entity) override;

private:
    int currentHealth = 0;
    bool startTimeOut = false;

    chrono::high_resolution_clock::time_point startTime;
};