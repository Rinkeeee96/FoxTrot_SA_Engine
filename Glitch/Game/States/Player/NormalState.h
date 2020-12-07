#pragma once
#include "Game/States/IState.h"
#include <chrono>

#define TIME_OUT_IN_SECONDS 2

class Player;

class NormalState : public IState<Player>
{
public:
    virtual ~NormalState() {}

    void entry(Player* entity) override;
    void execute(Player* entity) override;
    void exit(Player* entity) override;
private:
    int currentHealth;
    bool startTimeOut = false;

    chrono::high_resolution_clock::time_point startTime;
};