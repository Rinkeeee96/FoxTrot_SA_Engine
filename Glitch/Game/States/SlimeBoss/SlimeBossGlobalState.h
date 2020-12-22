#pragma once
#include "Game/States/IState.h"

class SlimeBoss;

/// @brief Class for the global player state
class SlimeBossGlobalState : public IState<SlimeBoss>
{
public:
    virtual ~SlimeBossGlobalState() {}

    void entry(SlimeBoss& entity) override;
    void execute(SlimeBoss& entity) override;
    void exit(SlimeBoss& entity) override;
};