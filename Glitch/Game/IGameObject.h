#pragma once
#include "Engine/SceneManager/Object.h"

class IGameObject : public Object {
public:
	IGameObject(const int id) : Object(id) {}
	virtual void onUpdate() = 0;
};