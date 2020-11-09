#pragma once
#include "Object.h"

struct Layer
{
	bool visible = true;
	bool render = false;
	vector<Object*> objects;
};