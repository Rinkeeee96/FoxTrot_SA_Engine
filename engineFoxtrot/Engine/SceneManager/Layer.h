#pragma once
#include "Object.h"

struct Layer
{
	bool render = false;
	map<int, Object*> objects;
};