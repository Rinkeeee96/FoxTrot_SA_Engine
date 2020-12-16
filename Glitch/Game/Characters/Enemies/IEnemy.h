#pragma once
#include "pch.h"
#include "Game/Characters/ICharacter.h"
#include "Game\Characters\Player\Player.h"
#include "Game/General/GeneralEnemyDefines.h"

/// @brief 
/// Enemy base class
class IEnemy : public ICharacter {
protected:
	Player* player = nullptr;
	int damage = 1;
public:
	IEnemy(EventDispatcher& dispatcher) : ICharacter(dispatcher) {}
	IEnemy(const int id, EventDispatcher& dispatcher) : ICharacter(id, dispatcher) {}
	virtual ~IEnemy() {}

	void setPlayer(Player* player) { this->player = player; }
	void doDamage() { this->player->removeHealth(this->damage); }

	virtual void onUpdate(float deltaTime) = 0;
	virtual ICharacter* clone(int id) = 0;
};