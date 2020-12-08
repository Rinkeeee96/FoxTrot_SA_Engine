#pragma once
#include "Game/Characters/ICharacter.h"
#include "Game/SpriteState.h"
#include "Game/Commands/GameKeypressInvoker.h"

#define RESTITUTION_CORRECTION 1

class Player : public ICharacter {
public:
	Player(EventDispatcher& _dispatcher) :ICharacter(_dispatcher) {};
	Player(const int id, EventDispatcher& dispatcher);
	/// @brief 
	/// Handles when an collision event begins, when the direction of the collision happend on the bottom side of the player object,
	/// set can jump true
	bool onCollisionBeginEvent(const Event& event);
	/// @brief 
	/// Handles when an collision event ends, when the direction of the collision happend on the bottom side of the player object, set can jump false
	bool onCollisionEndEvent(const Event& event);
	void setYAxisVelocity(const float val) override;
	void setXAxisVelocity(const float val) override;

	/// @brief 
	/// Handles when an key pressed event happend, Player can move right, left and jump
	bool onKeyPressed(const Event& event);

	/// @brief 
	/// Handles when an key released event happend, Player can move right, left and jump
	bool onKeyReleased(const Event& event);

	// @brief 
	/// Register the keypressinvoker from the builder to capture relevant keyevents and act on them accordingly
	void registerKeypressInvoker(GameKeypressInvoker* invoker);

	void onUpdate() override;

	ICharacter* clone(int id) override;

private:
	GameKeypressInvoker* invoker;
	bool releasedKeyLastFrame;
};