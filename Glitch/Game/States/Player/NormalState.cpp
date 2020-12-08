#include "pch.h"
#include "NormalState.h"
#include "InvinsibleState.h"
#include "Game/Characters/Player/Player.h"

void NormalState::entry(Player* entity) {
	entity->setCanHit(true);
	this->currentHealth = entity->getCurrentHealth();
};

void NormalState::execute(Player* entity) {
	if (entity->getCurrentHealth() != currentHealth) {
		entity->getStateMachine().changeState(new InvinsibleState, entity);
	}
};

void NormalState::exit(Player* entity) { 

};