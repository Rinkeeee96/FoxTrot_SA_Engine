#pragma once
#include "pch.h"
#include "Game/Characters/ICharacter.h"

/// @brief 
/// Enemy base class
class IEnemy : public ICharacter {
public:
	IEnemy() : ICharacter() {}
	IEnemy(const int id) : ICharacter(id) {}
	virtual ~IEnemy() {}

	virtual void onUpdate() = 0;
	virtual ICharacter* clone(int id) = 0;
};