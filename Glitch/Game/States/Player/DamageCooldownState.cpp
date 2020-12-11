#include "pch.h"
#include "DamageCooldownState.h"
#include "Game/Characters/Player/Player.h"
#include "NormalState.h"

/// @brief 
/// on entry sets player invincible on true
/// sets tint of player to red
void DamageCooldownState::entry(Player* entity) {
	entity->setInvincible(true); 
	startTime = chrono::high_resolution_clock::now();
	entity->setTint(255, 0, 43);
};

/// @brief 
/// executes checks wheter time in seconds has passed and sets state back to normal
void DamageCooldownState::execute(Player* entity) {
	chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
	chrono::seconds seconds = std::chrono::duration_cast<chrono::seconds>(endTime - startTime);

	if (seconds == std::chrono::seconds(TIME_OUT_IN_SECONDS)) {
		entity->getStateMachine().changeState(new NormalState, entity);
	}
};

/// @brief 
/// exit
void DamageCooldownState::exit(Player* entity) {
	entity->removeTint();
};