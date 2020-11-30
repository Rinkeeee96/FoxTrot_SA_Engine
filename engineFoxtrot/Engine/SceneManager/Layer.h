#pragma once
#include "Objects/Object.h"

struct Layer
{
	bool visible = true;
	bool render = false;
	bool alwaysVisible = false;
	bool renderPhysics = false;
	map<int, Object*> objects;
};