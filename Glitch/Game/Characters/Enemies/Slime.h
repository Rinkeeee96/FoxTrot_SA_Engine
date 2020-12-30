#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"

enum class SlimeType {
	Green,
	Ice
};

/// @brief 
/// Slime class with correspondending AI logic
class Slime : public BaseEnemy {
public:
	Slime(EventDispatcher& _dispatcher, SlimeType _type = SlimeType::Green) : BaseEnemy(_dispatcher), type{_type} {}
	Slime(const int id, EventDispatcher& _dispatcher, SlimeType _type = SlimeType::Green) : BaseEnemy(id, _dispatcher), type{ _type } {}

	void onUpdate(float deltaTime) override;

	map<SpriteState, shared_ptr<SpriteObject>> buildSpritemap(int textureId) override;

	shared_ptr<ICharacter> clone(int id) override { return shared_ptr<ICharacter>(new Slime(id, this->dispatcher)); }

private:
	float jumpTimer = 0;
	bool jumping = false;

	SlimeType type;

	map<SpriteState, shared_ptr<SpriteObject>> buildNormalSlimeMap(int textureId);
	map<SpriteState, shared_ptr<SpriteObject>> buildIceSlimeMap(int textureId);
};