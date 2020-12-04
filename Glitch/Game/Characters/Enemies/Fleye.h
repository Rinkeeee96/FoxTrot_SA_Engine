#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

#define RANGE 900

/// @brief 
/// Fleye class with correspondending AI logic
class Fleye : public IEnemy {
public:
	Fleye(EventDispatcher& _dispatcher) : IEnemy(_dispatcher) { this->setGravity(0); }
	Fleye(const int id, EventDispatcher& _dispatcher) : IEnemy(id, _dispatcher) {
		_dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Fleye::onCollisionBeginEvent));
		this->setGravity(0);
	}

	bool onCollisionBeginEvent(const Event& event);

	void onUpdate() override;

	map<SpriteState, SpriteObject*> buildSpritemap(int textureId) override;

	ICharacter* clone(int id) override { return new Fleye(id, this->dispatcher); }

private:
	bool goingUp = false;
	bool setup = true;
	float startY = 0;
};