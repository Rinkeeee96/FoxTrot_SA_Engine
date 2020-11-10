#pragma once
#include "Game/Characters/ICharacter.h"

class IEnemy : public ICharacter {
public:
	IEnemy(const int id) : ICharacter(id) {}

	virtual void onUpdate() = 0;
};