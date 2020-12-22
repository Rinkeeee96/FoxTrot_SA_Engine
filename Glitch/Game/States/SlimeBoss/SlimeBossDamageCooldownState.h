#pragma once
#include "Game/States/IState.h"
#include <chrono>

#define TIME_OUT_IN_SECONDS 1

class SlimeBoss;

/// @brief 
/// DamageCooldownState
class SlimeBossDamageCooldownState : public IState<SlimeBoss>
{
public:
    virtual ~SlimeBossDamageCooldownState() {}

    void entry(SlimeBoss& entity) override;
    void execute(SlimeBoss& entity) override;
    void exit(SlimeBoss& entity) override;

private:
    int currentHealth;
    bool startTimeOut = false;

    chrono::high_resolution_clock::time_point startTime;
};