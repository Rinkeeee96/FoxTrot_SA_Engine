#include "pch.h"
#include "SlimeBossNormalState.h"
#include "SlimeBossDamageCooldownState.h"
#include "Game/Characters/Enemies/SlimeBoss.h"

/// @brief on entry sets player invincible on false
/// @param entity 
void SlimeBossNormalState::entry(SlimeBoss& entity) {
	entity.setInvincible(false);
	this->currentHealth = entity.getCurrentHealth();
};

/// @brief if hit sets DamageCooldownState
/// @param entity 
void SlimeBossNormalState::execute(SlimeBoss& entity) {
	if (entity.getCurrentHealth() <= entity.getTotalHealth() / 2) {
		if (!this->triggered) {
			// todo spawn enemies
			entity.spawnEnemies();
			triggered = true;
		}
	}
	if (entity.getCurrentHealth() != currentHealth) {
		entity.getStateMachine().changeState(make_unique<SlimeBossDamageCooldownState>(), entity);
	}
};

/// @brief exit
/// @param entity 
void SlimeBossNormalState::exit(SlimeBoss& entity) {

};
