#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

/// @brief 
/// Slime class with correspondending AI logic
class Slime : public BaseEnemy {
public:
	Slime(EventDispatcher& _dispatcher) : BaseEnemy(_dispatcher) {}
	Slime(const int id, EventDispatcher& _dispatcher) : BaseEnemy(id, _dispatcher) {}

	void onUpdate(float deltaTime) override;

	map<SpriteState, SpriteObject*> buildSpritemap(int textureId) override;

	ICharacter* clone(int id) override { return new Slime(id, this->dispatcher); }

private:
	float jumpTimer = 0;
	bool jumping = false;
};