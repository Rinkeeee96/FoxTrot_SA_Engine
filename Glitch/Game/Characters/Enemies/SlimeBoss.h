#pragma once
#include "Game/Characters/Enemies/BaseEnemy.h"
#include "Game/States/StateMachine.h"
#include "Game/States/SlimeBoss/SlimeBossGlobalState.h"
#include "Game/States/SlimeBoss/SlimeBossNormalState.h"

class Level;

/// @brief 
/// Slime class with correspondending AI logic
class SlimeBoss : public IEnemy {
public:
	SlimeBoss(Level& _level, EventDispatcher& _dispatcher);
	SlimeBoss(Level& _level, const int id, EventDispatcher& _dispatcher);

	void onUpdate(float deltaTime) override;

	bool onCollisionBeginEvent(const Event& event);
	map<SpriteState, shared_ptr<SpriteObject>> buildSpritemap(int textureId) override;

	shared_ptr<ICharacter> clone(int id) override { return shared_ptr<ICharacter>(new SlimeBoss(level, id, this->dispatcher)); }

	StateMachine<SlimeBoss>& getStateMachine() { return this->stateMachine; }

	void createSlime(int id, int startingTextureId, float x, float y);
	void spawnEnemies();

	void setJumSpeedTime(float f) { this->jumpSpeedTimer = f; }
	float getJumSpeedTime() { return this->jumpSpeedTimer; }
private:
	float jumpTimer = 0;
	bool jumping = false;
	float jumpSpeedTimer = 2;
	Level& level;
	StateMachine<SlimeBoss> stateMachine;
};