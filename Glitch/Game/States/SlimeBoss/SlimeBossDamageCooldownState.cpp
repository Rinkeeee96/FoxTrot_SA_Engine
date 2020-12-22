#include "pch.h"
#include "SlimeBossDamageCooldownState.h"
#include "Game/Characters/Enemies/SlimeBoss.h"
#include "SlimeBossNormalState.h"

/// @brief 
/// on entry sets player invincible on true
/// sets tint of player to red
/// @param entity 
void SlimeBossDamageCooldownState::entry(SlimeBoss& entity) {
	entity.setInvincible(true);
	startTime = chrono::high_resolution_clock::now();
	entity.setTint(255, 0, 43);
};

/// @brief executes checks wheter time in seconds has passed and sets state back to normal
/// @param entity 
void SlimeBossDamageCooldownState::execute(SlimeBoss& entity) {
	chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
	chrono::seconds seconds = std::chrono::duration_cast<chrono::seconds>(endTime - startTime);

	if (seconds == std::chrono::seconds(TIME_OUT_IN_SECONDS)) {
		entity.getStateMachine().changeState(make_unique<SlimeBossNormalState>(), entity);
	}
};

/// @brief exit
/// @param entity 
void SlimeBossDamageCooldownState::exit(SlimeBoss& entity) {
	entity.removeTint();
};