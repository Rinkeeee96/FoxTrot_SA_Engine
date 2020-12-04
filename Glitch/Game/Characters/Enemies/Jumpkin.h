#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

#define HORIZONTAL_RANGE 900
#define VERTICAL_RANGE 150

//TODO Use deltaTime
#define JUMP_ANIMATION_TIME 100

/// @brief 
/// Jumpkin class with correspondending AI logic
class Jumpkin : public IEnemy {
public:
	Jumpkin(EventDispatcher& _dispatcher) : IEnemy(_dispatcher) {}
	Jumpkin(const int id, EventDispatcher& _dispatcher) : IEnemy(id, _dispatcher) {
		_dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Jumpkin::onCollisionBeginEvent));
	}

	bool onCollisionBeginEvent(const Event& event);

	void onUpdate() override;

	map<SpriteState, SpriteObject*> buildSpritemap(int textureId) override;

	ICharacter* clone(int id) override { return new Jumpkin(id, dispatcher); }

private:
	int jumpTimer = 0;
	bool jumping = false;
};