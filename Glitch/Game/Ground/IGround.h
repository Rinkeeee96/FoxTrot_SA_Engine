#pragma once
#include "Game/IGameObject.h"

class IGround : public IGameObject {
public:
	IGround(const int id) : IGameObject(id) {}

	virtual void onUpdate() = 0;
};

