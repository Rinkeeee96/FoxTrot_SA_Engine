#pragma once
#include "Game/Ground/IGround.h"

class BaseGround : public IGround {
public:
	BaseGround(const int id) : IGround(id) {}

	virtual void onUpdate() override {};
};