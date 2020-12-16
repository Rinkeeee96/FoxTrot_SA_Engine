#pragma once
#include "Game/IGameObject.h"
#include "Events/EventDispatcher.h"
#include "Game/SpriteState.h"

/// @brief 
/// Character base class; guarantees several functions being implementen in extended classes
class ICharacter : public IGameObject  {
public:
	ICharacter(EventDispatcher& _dispatcher) : dispatcher{ _dispatcher } {};
	ICharacter(const int id, EventDispatcher& _dispatcher) : dispatcher{ _dispatcher }, IGameObject(id) {}
	virtual ~ICharacter() {}

	virtual void onUpdate() = 0;

	bool getCanJump() const { return this->canJump; }
	void setCanJump(bool val) { this->canJump = val; }

	float getSpawnX() const { this->spawnX; }
	void setSpawnX(float val) { this->spawnX = val; }

	float getSpawnY() const { this->spawnY; }
	void setSpawnY(float val) { this->spawnY = val; }

	int getCurrentHealth() const { return this->currentHealth; }

	/// @brief Sets the current health of a character, if health is higher then max health the max health is set to current health
	/// @param val 
	void setCurrentHealth(int val) { 
		this->currentHealth = val; 
		if (currentHealth > totalHealth) totalHealth = currentHealth;
	}

	/// @brief Removes health from a character. If players current health is < 0 the kill function is called
	/// @param val 
	void removeHealth(int val) { 
		if (invincible) return;
		this->currentHealth -= val;
		if (this->currentHealth <= 0) {
			this->kill();
		}
	}

	int getTotalHealth() const { return this->totalHealth; }
	void setTotalHealth(int val) { this->totalHealth = val; }

	void kill() { this->currentHealth = 0; }
    void respawn() { this->setPositionX(spawnX); this->setPositionY(spawnY); }
	bool getIsDead() const { return this->currentHealth == 0; }

	/// @brief
	/// Builds the spritemap for an object, should be implemented when overriding this
	/// @param textureId
	/// The current texture id, required to be able to assign a unique id to all textures
	/// @returns map<SpriteState, SpriteObject*>
	virtual map<SpriteState, SpriteObject*> buildSpritemap(int textureId) = 0;

	void setInvincible(const bool invincible) { this->invincible = invincible; }
	bool getInvincible() const { return this->invincible; }
	virtual ICharacter* clone(int id) = 0;
protected:
	int currentHealth = 0;
	int totalHealth = 0;
	bool invincible = false;
	bool canJump = false;
	float spawnX = 0;
	float spawnY = 0;
	EventDispatcher& dispatcher;
};