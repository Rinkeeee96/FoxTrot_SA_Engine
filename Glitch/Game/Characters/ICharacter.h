#pragma once
#include "Game/IGameObject.h"

/// @brief 
/// Character base class
class ICharacter : public IGameObject  {
public:
	ICharacter() : IGameObject() {}
	ICharacter(const int id) : IGameObject(id) {}
	virtual ~ICharacter() {}

	virtual void onUpdate() = 0;

	bool getCanJump() const { this->canJump; }
	void setCanJump(bool val) { this->canJump = val; }
	int getHealth() const { this->health; }
	void setHealth(int val) { this->health = val; }
	void removeHealth(int val) { 
		this->health -= val;
		if (this->health <= 0) {
			this->kill();
		}
	}

	void kill() { this->isDead = true; this->health = 0; }
	bool getIsDead() const { return this->isDead; }

	virtual ICharacter* clone(int id) = 0;
protected:
	int health = 0;
	bool canJump = false;
};