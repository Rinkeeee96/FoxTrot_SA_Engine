#pragma once
#include "Game/IGameObject.h"

class ICharacter : public IGameObject  {
public:
	ICharacter() : IGameObject() {}
	ICharacter(const int id) : IGameObject(id) {}
	virtual ~ICharacter() {}

	virtual void onUpdate() = 0;

	bool getCanJump() const { this->canJump; }
	void setCanJump(const bool val) { this->canJump = val; }
	int getHealth() const { this->health; }
	void setHealth(const int val) { this->health = val; }
	void setIsDead(const bool val) { this->isDead = val; }
	bool getIsDead() const { return this->isDead; }

	virtual ICharacter* clone(int id) = 0;
protected:
	bool isDead = false;
	int health = 0;
	bool canJump = false;
};