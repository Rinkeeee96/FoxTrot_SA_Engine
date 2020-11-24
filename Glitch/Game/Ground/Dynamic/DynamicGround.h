#pragma once
#include "Game/Ground/IGround.h"

/// @brief 
/// "Normal" ground class
class DynamicGround : public IGround {
public:
	DynamicGround(const int id) : IGround(id) {}

	virtual void onUpdate() override {};
};