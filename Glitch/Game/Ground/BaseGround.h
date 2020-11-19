#pragma once
#include "Game/Ground/IGround.h"

/// @brief 
/// "Normal" ground class
class BaseGround : public IGround {
public:
	BaseGround(const int id) : IGround(id) {}

	virtual void onUpdate() override {};
};