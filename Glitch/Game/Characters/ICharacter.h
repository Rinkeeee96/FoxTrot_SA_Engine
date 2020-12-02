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
	bool getIsDead() const { return this->currentHealth == 0; }

	virtual ICharacter* clone(int id) = 0;
protected:
	int currentHealth = 0;
	int totalHealth = 0;
	bool canJump = false;
	EventDispatcher& dispatcher;
};