#pragma once
#include <api.h>
#include <Engine\Events\Action\ObjectStopEvent.h>
#include "Game/Characters/ICharacter.h"
#include "Game/SpriteState.h"

class Player : public ICharacter {
public:
	Player() : ICharacter(-1) {};
	Player(const int id);
	/// @brief 
	/// Handles when an collision event begins, when the direction of the collision happend on the bottom side of the player object,
	/// set can jump true
	void onCollisionBeginEvent(Event& event);
	/// @brief 
	/// Handles when an collision event ends, when the direction of the collision happend on the bottom side of the player object, set can jump false
	void onCollisionEndEvent(Event& event);
	void setYAxisVelocity(const float val) override;
	void setXAxisVelocity(const float val) override;
	/// @brief 
	/// Handles when an key pressed event happend, Player can move right, left and jump
	void onKeyPressed(Event& event);

	void onKeyReleased(Event& event);

	void onUpdate() override {};

	virtual ICharacter* clone(int id) override {
		return new Player(id);
	}
private:
	bool canJump = false;
};