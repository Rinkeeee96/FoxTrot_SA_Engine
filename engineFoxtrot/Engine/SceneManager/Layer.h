#pragma once
#include "Objects/Object.h"

struct Layer
{
	bool render = false;
	map<int, Object*> objects;
};