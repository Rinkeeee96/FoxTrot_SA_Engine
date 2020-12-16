#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

#define JUMPKIN_HORIZONTAL_RANGE 900
#define JUMPKIN_VERTICAL_RANGE 150

#define JUMPKIN_SPRITE_HEIGHT 43
#define JUMPKIN_SPRITE_WIDTH 32
#define JUMPKIN_SPRITE_WIDTH_SHORT 30

//TODO Use deltaTime
#define JUMPKIN_JUMP_ANIMATION_TIME 100

/// @brief 
/// Jumpkin class with correspondending AI logic
class Jumpkin : public BaseEnemy {
public:
	Jumpkin(EventDispatcher& _dispatcher) : BaseEnemy(_dispatcher) {}
	Jumpkin(const int id, EventDispatcher& _dispatcher) : BaseEnemy(id, _dispatcher) {}

	void onUpdate() override;

	map<SpriteState, shared_ptr<SpriteObject>> buildSpritemap(int textureId) override;

	shared_ptr<ICharacter> clone(int id) override { return shared_ptr<ICharacter>(new Jumpkin(id, dispatcher)); }

private:
	int jumpTimer = 0;
	bool jumping = false;
};