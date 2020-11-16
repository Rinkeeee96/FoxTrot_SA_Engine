#pragma once
#include <api.h>
#include <Engine\Events\Action\ObjectStopEvent.h>
#include "Game/Characters/ICharacter.h"
#include "Game/SpriteState.h"

class Player : public ICharacter {
public:
	Player() : ICharacter() {};
	Player(const int id);
	/// @brief 
	/// Handles when an collision event begins, when the direction of the collision happend on the bottom side of the player object,
	/// set can jump true
	bool onCollisionBeginEvent(Event& event);
	/// @brief 
	/// Handles when an collision event ends, when the direction of the collision happend on the bottom side of the player object, set can jump false
	bool onCollisionEndEvent(Event& event);
	void setYAxisVelocity(const float val) override;
	void setXAxisVelocity(const float val) override;
	/// @brief 
	/// Handles when an key pressed event happend, Player can move right, left and jump
	bool onKeyPressed(Event& event);
	// @brief 
	/// Handles when an key released event happend, stop moving
	bool onKeyReleased(Event& event);

	void onUpdate() override {};

	virtual ICharacter* clone(int id) override;
private:
	bool canJump = false;
};