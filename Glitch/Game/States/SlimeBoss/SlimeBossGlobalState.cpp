#include "pch.h"
#include "SlimeBossGlobalState.h"
#include "Game/Characters/Enemies/SlimeBoss.h"

/// @brief execute
/// @param entity 
void SlimeBossGlobalState::execute(SlimeBoss& entity) {
	if (entity.getCurrentHealth() <= entity.getTotalHealth() / 3 * 2) {

		if (!this->upgradeTrigger1) {
			entity.setSpeed(entity.getSpeed() + 0.7);
			entity.setJumSpeedTime(0.9);
			entity.spawnEnemies();
			upgradeTrigger1 = true;
		}
	}
	if (entity.getCurrentHealth() <= entity.getTotalHealth() / 3 * 1) {

		if (!this->upgradeTrigger2) {
			entity.spawnEnemies();
			upgradeTrigger2 = true;
		}
	}
}

/// @brief on entry sets player invincible on false
/// @param entity 
void SlimeBossGlobalState::entry(SlimeBoss& entity) { };

/// @brief exit
/// @param entity 
void SlimeBossGlobalState::exit(SlimeBoss& entity) {

};