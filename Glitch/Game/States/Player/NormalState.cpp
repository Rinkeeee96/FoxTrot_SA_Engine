#include "pch.h"
#include "NormalState.h"
#include "DamageCooldownState.h"
#include "Game/Characters/Player/Player.h"

/// @brief on entry sets player invincible on false
/// @param entity 
void NormalState::entry(Player& entity) {
	entity.setInvincible(false);
	this->currentHealth = entity.getCurrentHealth();
};

/// @brief if hit sets DamageCooldownState
/// @param entity 
void NormalState::execute(Player& entity) {
	if (entity.getCurrentHealth() != currentHealth) {
		entity.getStateMachine().changeState(make_unique<DamageCooldownState>(), entity);
	}
};

/// @brief exit
/// @param entity 
void NormalState::exit(Player& entity) {

};