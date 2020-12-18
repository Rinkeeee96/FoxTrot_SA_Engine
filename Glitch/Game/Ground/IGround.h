#pragma once
#include "Game/IGameObject.h"

/// @brief 
/// Ground interface
class IGround : public IGameObject {
public:
	IGround(const int id) : IGameObject(id) {}

	virtual void onUpdate(float deltaTime) = 0;
};

