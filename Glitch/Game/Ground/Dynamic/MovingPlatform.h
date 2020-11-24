#pragma once
#include "Game/Ground/Dynamic/DynamicGround.h"

#define RANGE 400
#define SPEED 200

/// @brief 
/// Moving platform (Dynamic ground)
class MovingPlatform : public DynamicGround {
public:
	MovingPlatform(const int id) : DynamicGround(id) {
		//this->setGravity(0);
		this->setSpeed(0);
		this->setJumpHeight(5);
		this->setDensity(200);
		this->setFriction(0);
		this->setRestitution(0);
		this->setBodyType(BodyType::Kinematic);
		this->setRotatable(false);
	}

	void setPositionY(const float val) override {

		Object::setPositionY(val);
	}
	void setPositionX(const float val) override {
		Object::setPositionX(val);
	}

	void onUpdate() override {
		EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
	};

private:	
	float baseY = 0;
};