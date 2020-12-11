#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

/// @brief 
/// BaseEnemy class; Unites the onCollisionEvent for every enemy
class BaseEnemy : public IEnemy {
public:
	BaseEnemy(EventDispatcher& _dispatcher) : IEnemy(_dispatcher) {}
	BaseEnemy(const int id, EventDispatcher& _dispatcher) : IEnemy(id, _dispatcher) {
		_dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(BaseEnemy::onCollisionBeginEvent));
	}

	/// @brief
	///  Event handler for handling collision after event
	bool onCollisionBeginEvent(const Event& event);

private:
	int jumpTimer = 0;
	bool jumping = false;
};