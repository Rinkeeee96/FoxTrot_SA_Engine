#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

#define FLEYE_RANGE 900

/// @brief 
/// Fleye class with correspondending AI logic
class Fleye : public BaseEnemy {
public:
	Fleye(EventDispatcher& _dispatcher) : BaseEnemy(_dispatcher) { this->setGravity(0); }
	Fleye(const int id, EventDispatcher& _dispatcher) : BaseEnemy(id, _dispatcher) {
		this->setGravity(0);
	}

	void onUpdate() override;

	map<SpriteState, SpriteObject*> buildSpritemap(int textureId) override;

	ICharacter* clone(int id) override { return new Fleye(id, this->dispatcher); }

private:
	bool goingUp = false;
	bool setup = true;
	float startY = 0;
};