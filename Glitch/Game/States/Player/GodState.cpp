#include "pch.h"
#include "GodState.h"
#include "Game/Characters/Player/Player.h"

void GodState::entry(Player* entity) {
	entity->setCanHit(false);
	entity->setTint(255, 251, 135);
};

void GodState::execute(Player* entity) {
	entity->setCanJump(true);
	entity->setTotalHealth(3);
	entity->setCurrentHealth(3);
};

void GodState::exit(Player* entity) {
	entity->removeTint();
};