#pragma once
#include <Game/Characters/Enemies/Slime.h>

class MockSlime : public Slime {
public:
	MockSlime(int _id, EventDispatcher& _dispatcher) : Slime(_id, _dispatcher) {
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
