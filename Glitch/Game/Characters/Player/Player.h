#pragma once
#include "Game/Characters/ICharacter.h"
#include "Game/SpriteState.h"

#define RESTITUTION_CORRECTION 1
#define PLAYER_SPRITE_HEIGHT 37
#define PLAYER_SPRITE_WIDTH 50

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
	// @brief 
	/// Handles when an key released event happend, stop moving
	bool onKeyReleased(const Event& event);

	void onUpdate(float deltaTime) override {};

	map<SpriteState, SpriteObject*> buildSpritemap(int textureId) override;

	ICharacter* clone(int id) override;
};