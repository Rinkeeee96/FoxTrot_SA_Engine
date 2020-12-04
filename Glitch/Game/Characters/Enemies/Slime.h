#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

//TODO Use deltaTime
#define JUMP_ANIMATION_TIME 50

/// @brief 
/// Slime class with correspondending AI logic
class Slime : public IEnemy {
public:
	Slime(EventDispatcher& _dispatcher) : IEnemy(_dispatcher) {}
	Slime(const int id, EventDispatcher& _dispatcher) : IEnemy(id, _dispatcher) {
		_dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Slime::onCollisionBeginEvent));
	}

	bool onCollisionBeginEvent(const Event& event);

	void onUpdate() override;

	map<SpriteState, SpriteObject*> buildSpritemap(int textureId) override;

	ICharacter* clone(int id) override { return new Slime(id, this->dispatcher); }

private:
	int jumpTimer = 0;
	bool jumping = false;
};