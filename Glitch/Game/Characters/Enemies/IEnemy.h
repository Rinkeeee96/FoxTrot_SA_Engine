#pragma once
#include "pch.h"
#include "Game/Characters/ICharacter.h"
#include "Game\Characters\Player\Player.h"

/// @brief 
/// Enemy base class
class IEnemy : public ICharacter {
protected:
	Player* player = nullptr;
public:
	IEnemy(shared_ptr<EventDispatcher> dispatcher) : ICharacter(dispatcher) {}
	IEnemy(const int id, shared_ptr<EventDispatcher> dispatcher) : ICharacter(id, dispatcher) {}
	virtual ~IEnemy() {}

	void setPlayer(Player* player) {
		this->player = player;
	}

	virtual void onUpdate() = 0;
	virtual ICharacter* clone(int id) = 0;
};