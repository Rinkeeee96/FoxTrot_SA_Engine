#pragma once
#include "Game/Ground/Dynamic/DynamicGround.h"

#define RANGE 400
#define SPEED 200

/// @brief 
/// Moving platform (Dynamic ground)
class MovingPlatform : public DynamicGround {
public:
	MovingPlatform(const int id) : DynamicGround(id) {
		this->setGravity(0);
	}

	void onUpdate() override {
		/*if (this->getYAxisVelocity() == 0) {
			this->setYAxisVelocity(-1 * SPEED);
		}*/
	};

private:	
	float baseY = 0;
};