#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

#define SLIME_IDLE_SPRITE_WIDTH 31
#define SLIME_IDLE_SPRITE_HEIGHT 23

#define SLIME_ACTION_SPRITE_WIDTH 33
#define SLIME_ACTION_SPRITE_HEIGHT 24

#define SLIME_JUMP_ANIMATION_TIME 2

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