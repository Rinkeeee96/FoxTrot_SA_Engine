#pragma once
#include "Game/Characters/ICharacter.h"

class IEnemy : public ICharacter {
public:
	IEnemy() : ICharacter() {}
	IEnemy(const int id) : ICharacter(id) {}
	virtual ~IEnemy() {}

	virtual void onUpdate() = 0;
	virtual ICharacter* clone(int id) = 0;
};