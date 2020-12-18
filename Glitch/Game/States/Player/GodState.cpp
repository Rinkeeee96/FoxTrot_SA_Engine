#include "pch.h"
#include "GodState.h"
#include "Game/Characters/Player/Player.h"

/// @brief	on entry sets player invincible on true
///			sets tint of player to gold
/// @param entity 
void GodState::entry(Player& entity) {
	entity.setInvincible(true);
	entity.setTint(255, 251, 135);
};

/// @brief execute player health etc to max, cant die
/// @param entity 
void GodState::execute(Player& entity) {
	entity.setCanJump(true);
	entity.setCurrentHealth(entity.getTotalHealth());
};

/// @brief exit
/// @param entity 
void GodState::exit(Player& entity) {
	entity.removeTint();
};