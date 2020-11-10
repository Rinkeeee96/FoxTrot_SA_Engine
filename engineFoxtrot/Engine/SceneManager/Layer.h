#pragma once
#include "Objects/Object.h"

struct Layer
{
	bool render = false;
	vector<Object*> objects;
};