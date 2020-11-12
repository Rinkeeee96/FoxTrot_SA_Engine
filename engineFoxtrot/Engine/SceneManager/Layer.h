#pragma once
#include "Object.h"

struct Layer
{
	bool visible = true;
	bool render = false;
	bool renderPhysics = false;
	vector<Object*> objects;
};