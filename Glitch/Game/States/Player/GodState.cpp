#include "pch.h"
#include "GodState.h"
#include "Game/Characters/Player/Player.h"

/// @brief 
/// on entry sets player invincible on true
/// sets tint of player to gold
void GodState::entry(Player* entity) {
	entity->setInvincible(true);
	entity->setTint(255, 251, 135);
};

/// @brief 
/// execute player health etc to max, cant die
void GodState::execute(Player* entity) {
	entity->setCanJump(true);
	entity->setTotalHealth(3);
	entity->setCurrentHealth(3);
};

/// @brief 
/// exit
void GodState::exit(Player* entity) {
	entity->removeTint();
};