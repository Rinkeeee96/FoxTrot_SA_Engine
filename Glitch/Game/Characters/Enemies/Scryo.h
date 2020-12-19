#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

/// @brief 
/// Scryo class with correspondending AI logic
class Scryo : public BaseEnemy {
public:
	Scryo(EventDispatcher& _dispatcher) : BaseEnemy(_dispatcher) { this->setGravity(0); }
	Scryo(const int id, EventDispatcher& _dispatcher) : BaseEnemy(id, _dispatcher) {
		this->setGravity(0);
		this->damage = 2;
	}

	void onUpdate(float deltaTime) override;

	map<SpriteState, shared_ptr<SpriteObject>> buildSpritemap(int textureId) override;

	shared_ptr<ICharacter> clone(int id) override { return shared_ptr<ICharacter>(new Scryo(id, this->dispatcher)); }

private:
	bool goingUp = false;
	bool setup = true;
	float startY = 0;
};