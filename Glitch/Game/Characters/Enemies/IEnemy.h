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
	IEnemy() : ICharacter() {}
	IEnemy(const int id) : ICharacter(id) {}
	virtual ~IEnemy() {}

	void setPlayer(Player* player) {
		this->player = player;
	}

	virtual void onUpdate() = 0;
	virtual ICharacter* clone(int id) = 0;
};