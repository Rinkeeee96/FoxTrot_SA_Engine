#include "pch.h"
#include "NormalState.h"
#include "DamageCooldownState.h"
#include "Game/Characters/Player/Player.h"

/// @brief 
/// on entry sets player invincible on false
void NormalState::entry(Player* entity) {
	entity->setInvincible(false);
	this->currentHealth = entity->getCurrentHealth();
};

/// @brief 
/// if hit sets DamageCooldownState
void NormalState::execute(Player* entity) {
	if (entity->getCurrentHealth() != currentHealth) {
		entity->getStateMachine().changeState(new DamageCooldownState, entity);
	}
};

/// @brief 
/// exit
void NormalState::exit(Player* entity) { 

};