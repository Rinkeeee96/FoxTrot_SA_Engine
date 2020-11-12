#pragma once
#include "Object.h"

struct Layer
{
	bool visible = true;
	bool render = false;
	map<int, Object*> objects;
	bool renderPhysics = false;
};