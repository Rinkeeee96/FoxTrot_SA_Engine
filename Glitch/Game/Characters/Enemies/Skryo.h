#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

/// @brief 
/// Skryo class with correspondending AI logic
class Skryo : public BaseEnemy {
public:
	Skryo(EventDispatcher& _dispatcher) : BaseEnemy(_dispatcher) { this->setGravity(0); }
	Skryo(const int id, EventDispatcher& _dispatcher) : BaseEnemy(id, _dispatcher) {
		this->setGravity(0);
		this->damage = 2;
	}

	void onUpdate(float deltaTime) override;

	map<SpriteState, shared_ptr<SpriteObject>> buildSpritemap(int textureId) override;

	shared_ptr<ICharacter> clone(int id) override { return shared_ptr<ICharacter>(new Skryo(id, this->dispatcher)); }

private:
	bool goingUp = false;
	bool setup = true;
	float startY = 0;
};