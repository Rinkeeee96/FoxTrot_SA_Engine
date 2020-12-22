#pragma once
#include "Game/States/IState.h"
#include <chrono>

class SlimeBoss;

/// @brief 
/// Default state of a player
class SlimeBossTransformState : public IState<SlimeBoss>
{
public:
    virtual ~SlimeBossTransformState() {}

    void entry(SlimeBoss& entity) override;
    void execute(SlimeBoss& entity) override;
    void exit(SlimeBoss& entity) override;

private:
    int currentHealth = 0;
    bool startTimeOut = false;

    chrono::high_resolution_clock::time_point startTime;
};