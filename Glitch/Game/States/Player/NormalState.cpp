#include "pch.h"
#include "NormalState.h"
#include "DamageCooldownState.h"
#include "Game/Characters/Player/Player.h"

void NormalState::entry(Player* entity) {
	entity->setInvincible(false);
	this->currentHealth = entity->getCurrentHealth();
};

void NormalState::execute(Player* entity) {
	if (entity->getCurrentHealth() != currentHealth) {
		entity->getStateMachine().changeState(new DamageCooldownState, entity);
	}
};

void NormalState::exit(Player* entity) { 

};