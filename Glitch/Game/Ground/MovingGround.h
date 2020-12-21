#pragma once
#include "Game/Ground/IGround.h"

/// @brief 
/// "Normal" ground class
class MovingGround : public IGround {
public:
	MovingGround(const int id) : IGround(id) {}

	virtual void onUpdate(float deltaTime) override {};
};