#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

/// @brief 
/// Jumpkin class with correspondending AI logic
class Jumpkin : public BaseEnemy {
public:
	Jumpkin(EventDispatcher& _dispatcher) : BaseEnemy(_dispatcher) {}
	Jumpkin(const int id, EventDispatcher& _dispatcher) : BaseEnemy(id, _dispatcher) {}

	void onUpdate(float deltaTime) override;

	map<SpriteState, SpriteObject*> buildSpritemap(int textureId) override;

	ICharacter* clone(int id) override { return new Jumpkin(id, dispatcher); }

private:
	float jumpTimer = 0;
	bool jumping = false;
};