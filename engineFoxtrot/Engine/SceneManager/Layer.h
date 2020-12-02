#pragma once
#include "Objects/Object.h"

struct Layer
{
	bool visible = true;
	bool render = false;
	bool alwaysVisible = false;
	bool renderPhysics = false;
	// TODO clear on scene detach in destructor
	map<int, Object*> objects;
};