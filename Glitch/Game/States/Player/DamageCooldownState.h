#pragma once
#include "Game/States/IState.h"
#include <chrono>

#define TIME_OUT_IN_SECONDS 2

class Player;

/// @brief 
/// DamageCooldownState
class DamageCooldownState : public IState<Player>
{
public:
    virtual ~DamageCooldownState() {}
    /// @brief 
    /// on entry sets player invincible on true
    /// sets tint of player to red
    void entry(Player* entity) override;

    /// @brief 
    /// executes checks wheter time in seconds has passed and sets state back to normal
    void execute(Player* entity) override;
    /// @brief 
    /// exit
    void exit(Player* entity) override;
private:
    int currentHealth;
    bool startTimeOut = false;

    chrono::high_resolution_clock::time_point startTime;
};