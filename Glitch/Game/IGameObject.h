#pragma once
#include "Engine/SceneManager/Object.h"

class IGameObject : public Object {
public:
	IGameObject() : Object(-1) {}
	IGameObject(const int id) : Object(id) {}
	virtual ~IGameObject() {}

	virtual void onUpdate() = 0;
};