#pragma once
#include "Game/IGameObject.h"

class ICharacter : public IGameObject  {
public:
	ICharacter(const int id) : IGameObject(id) {}
	virtual void onUpdate() = 0;
};