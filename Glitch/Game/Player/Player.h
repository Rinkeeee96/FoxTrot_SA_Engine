#pragma once
#include "../SpriteState.h"

class Player : public Drawable {
public:
	Player(const int _id);
	/// @brief 
	/// Handles when an collision event begins, when the direction of the collision happend on the bottom side of the player object, 
	/// set can jump true
	bool onCollisionBeginEvent(Event& event);
	/// @brief 
	/// Handles when an collision event ends, when the direction of the collision happend on the bottom side of the player object, set can jump false
	bool onCollisionEndEvent(Event& event);
	void setYAxisVelocity(const float val) override;

	/// @brief 
	/// Handles when an key pressed event happend, Player can move right, left and jump
	bool onKeyPressed(Event& event);

	bool getCanJump() const;
	void setCanJump(bool val);
private:
	bool canJump = false;
};