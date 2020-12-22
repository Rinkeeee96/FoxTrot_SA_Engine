#pragma once
#include "Game/States/IState.h"
#include <chrono>

class SlimeBoss;

/// @brief 
/// Default state of a player
class SlimeBossNormalState : public IState<SlimeBoss>
{
public:
    virtual ~SlimeBossNormalState() {}

    void entry(SlimeBoss& entity) override;
    void execute(SlimeBoss& entity) override;
    void exit(SlimeBoss& entity) override;

private:
    int currentHealth = 0;
    bool startTimeOut = false;
    bool triggered = false;

    chrono::high_resolution_clock::time_point startTime;
};