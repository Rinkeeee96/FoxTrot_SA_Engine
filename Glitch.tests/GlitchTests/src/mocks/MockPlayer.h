#pragma once
#include <Game/Characters/Player/Player.h>

class MockPlayer : public Player {
public:
	MockPlayer(int _id, EventDispatcher& _dispatcher) : Player(_id, _dispatcher) {
		this->setWidth(50);
		this->setHeight(50);

		this->setSpeed(100);
		this->setJumpHeight(4);
		this->setDensity(1000000);
		this->setFriction(0);
		this->setRestitution(0);
		this->setStatic(false);
	}
	void onUpdate(float frameData) override { }
};
