#pragma once
#include "Game/Characters/ICharacter.h"
#include "Game/SpriteState.h"
#include "Game/Commands/GameKeypressInvoker.h"
#include "Game/States/StateMachine.h"
#include "Game/States/Player/PlayerGlobalState.h"
#include "Game/States/Player/NormalState.h"

#include "Game/Commands/CharacterCommands/StopMovementCommand.h"

#define RESTITUTION_CORRECTION 1
#define PLAYER_SPRITE_HEIGHT 37
#define PLAYER_SPRITE_WIDTH 50

/// @brief
/// Handles player logic, stats and movement
class Player : public ICharacter {
	bool releasedKeyLastFrame;
public:
	Player(EventDispatcher& _dispatcher);
	Player(const int id, EventDispatcher& dispatcher);
	
	
	bool onCollisionBeginEvent(const Event& event);
	bool onCollisionEndEvent(const Event& event);

	void setYAxisVelocity(const float val) override;
	void setXAxisVelocity(const float val) override;

	// @brief 
	/// Register the keypressinvoker from the builder to capture relevant keyevents and act on them accordingly
	void registerKeypressInvoker(GameKeypressInvoker* invoker);

	map<SpriteState, SpriteObject*> buildSpritemap(int textureId) override;

	void onUpdate(float deltaTime) override {
		if (releasedKeyLastFrame)
		{
			StopMovementCommand(*this, "stopMovement").execute(this->dispatcher);
		}
		stateMachine.update(this);
	};
	
	StateMachine<Player>& getStateMachine() { return this->stateMachine; }
	ICharacter* clone(int id) override;
private:
	GameKeypressInvoker* invoker; 
	StateMachine<Player> stateMachine;
};