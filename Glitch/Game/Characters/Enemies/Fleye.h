#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

/// @brief 
/// Fleye class with correspondending AI logic
class Fleye : public BaseEnemy {
public:
	Fleye(EventDispatcher& _dispatcher) : BaseEnemy(_dispatcher) { this->setGravity(0); }
	Fleye(const int id, EventDispatcher& _dispatcher) : BaseEnemy(id, _dispatcher) {
		this->setGravity(0);
		this->damage = 2;
		this->setScale(1);
	}

	void onUpdate(float deltaTime) override;

	map<SpriteState, shared_ptr<SpriteObject>> buildSpritemap(int textureId) override;

	shared_ptr<ICharacter> clone(int id) override { return shared_ptr<ICharacter>(new Fleye(id, this->dispatcher)); }

private:
	bool goingUp = false;
	bool setup = true;
	float startY = 0;
};