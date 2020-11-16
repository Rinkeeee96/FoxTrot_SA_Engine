#pragma once
#include "Engine/SceneManager/Objects/Drawable.h"

class IGameObject : public Drawable {
public:
	IGameObject() : Drawable(-1) {}
	IGameObject(const int id) : Drawable(id) {}
	virtual ~IGameObject() {}

	virtual void onUpdate() = 0;
};