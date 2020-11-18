#pragma once
#include "api.h"

/// @brief 
/// Gameobject base class
class IGameObject : public Drawable {
public:
	IGameObject() : Drawable() {}
	IGameObject(const int id) : Drawable(id) {}
	virtual ~IGameObject() {}

	virtual void onUpdate() = 0;
};