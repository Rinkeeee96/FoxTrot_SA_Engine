#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

#define JUMPKIN_HORIZONTAL_RANGE 900
#define JUMPKIN_VERTICAL_RANGE 150

#define JUMPKIN_SPRITE_HEIGHT 43
#define JUMPKIN_SPRITE_WIDTH 32
#define JUMPKIN_SPRITE_WIDTH_SHORT 30

#define JUMPKIN_JUMP_ANIMATION_TIME 2

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