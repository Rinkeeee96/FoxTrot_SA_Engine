#pragma once
#include "Game/Characters/ICharacter.h"
#include "Game/SpriteState.h"
#include "Game/Commands/GameKeypressInvoker.h"
#include "Game/States/StateMachine.h"
#include "Game/States/Player/PlayerGlobalState.h"
#include "Game/States/Player/NormalState.h"

#include "Game/Commands/CharacterCommands/StopMovementCommand.h"

#define RESTITUTION_CORRECTION 1

class Player : public ICharacter {
	bool releasedKeyLastFrame;
public:
	Player(EventDispatcher& _dispatcher);
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

	// @brief 
	/// Register the keypressinvoker from the builder to capture relevant keyevents and act on them accordingly
	void registerKeypressInvoker(GameKeypressInvoker* invoker);

	void onUpdate() override {
		stateMachine.update(this);
		if (releasedKeyLastFrame)
		{
			StopMovementCommand(*this, "stopMovement").execute(this->dispatcher);
		}
	};
	StateMachine<Player>& getStateMachine() { return this->stateMachine; }
	ICharacter* clone(int id) override;
private:
	GameKeypressInvoker* invoker; 
	StateMachine<Player> stateMachine;
};