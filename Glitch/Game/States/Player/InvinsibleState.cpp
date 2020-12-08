#include "pch.h"
#include "InvinsibleState.h"
#include "Game/Characters/Player/Player.h"
#include "NormalState.h"

void InvinsibleState::entry(Player* entity) {
	entity->setCanHit(false); 
	startTime = chrono::high_resolution_clock::now();
	entity->setTint(255, 0, 43);
};

void InvinsibleState::execute(Player* entity) {
	chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
	chrono::seconds seconds = std::chrono::duration_cast<chrono::seconds>(endTime - startTime);

	if (seconds == std::chrono::seconds(TIME_OUT_IN_SECONDS)) {
		entity->getStateMachine().changeState(new NormalState, entity);
	}
};

void InvinsibleState::exit(Player* entity) {
	entity->removeTint();
};