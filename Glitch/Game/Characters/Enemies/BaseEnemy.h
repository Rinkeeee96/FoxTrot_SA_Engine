#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

#define SLIME_IDLE_SPRITE_WIDTH 31
#define SLIME_IDLE_SPRITE_HEIGHT 23

#define SLIME_ACTION_SPRITE_WIDTH 33
#define SLIME_ACTION_SPRITE_HEIGHT 24

//TODO Use deltaTime
#define JUMP_ANIMATION_TIME 50

/// @brief 
/// BaseEnemy class; Unites the onCollisionEvent for every enemy
class BaseEnemy : public IEnemy {
public:
	BaseEnemy(EventDispatcher& _dispatcher) : IEnemy(_dispatcher) {}
	BaseEnemy(const int id, EventDispatcher& _dispatcher) : IEnemy(id, _dispatcher) {
		_dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(BaseEnemy::onCollisionBeginEvent));
	}

	bool onCollisionBeginEvent(const Event& event);

private:
	int jumpTimer = 0;
	bool jumping = false;
};