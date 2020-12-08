#pragma once
#include "Game/States/IState.h"

class Player;

/// @brief 
/// God state of player
class GodState : public IState<Player>
{
public:
    virtual ~GodState() {}
    /// @brief 
    /// on entry sets player invincible on true
    /// sets tint of player to gold
    void entry(Player* entity) override;
    /// @brief 
    /// execute player health etc to max, cant die
    void execute(Player* entity) override;
    /// @brief 
    /// exit
    void exit(Player* entity) override;
private:

};