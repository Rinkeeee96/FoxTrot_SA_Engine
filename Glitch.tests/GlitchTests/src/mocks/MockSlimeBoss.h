#pragma once
#include <Game/Characters/Enemies/SlimeBoss.h>

class MockSlimeBoss : public SlimeBoss {
public:
	MockSlimeBoss(Level& _level, int _id, EventDispatcher& _dispatcher) : SlimeBoss(_level, _id, _dispatcher) {
		this->setWidth(50);
		this->setHeight(50);

		this->setSpeed(100);
		this->setJumpHeight(4);
		this->setDensity(1000000);
		this->setFriction(0);
		this->setRestitution(0);
		this->setStatic(false);
	}
};
