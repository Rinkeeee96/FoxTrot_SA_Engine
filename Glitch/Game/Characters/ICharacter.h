#pragma once
#include "Game/IGameObject.h"
#include "Events/EventDispatcher.h"

/// @brief 
/// Character base class
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

	int getHealth() const { this->health; }
	void setHealth(int val) { this->health = val; }

	int getCurrentHealth() const { return this->currentHealth; }
	void setCurrentHealth(int val) { 
		this->currentHealth = val; 
		if (currentHealth > totalHealth) totalHealth = currentHealth;
	}
	void removeHealth(int val) { 
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

	virtual ICharacter* clone(int id) = 0;
protected:
	int currentHealth = 0;
	int totalHealth = 0;
	bool canJump = false;
	float spawnX = 0;
	float spawnY = 0;
	EventDispatcher& dispatcher;
};