#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

/// @brief 
/// Slime class with correspondending AI logic
class SlimeBoss : public BaseEnemy {
public:
	SlimeBoss(EventDispatcher& _dispatcher) : BaseEnemy(_dispatcher) {}
	SlimeBoss(const int id, EventDispatcher& _dispatcher) : BaseEnemy(id, _dispatcher) {}

	void onUpdate(float deltaTime) override;

	map<SpriteState, shared_ptr<SpriteObject>> buildSpritemap(int textureId) override;

	shared_ptr<ICharacter> clone(int id) override { return shared_ptr<ICharacter>(new SlimeBoss(id, this->dispatcher)); }

private:
	float jumpTimer = 0;
	bool jumping = false;
};