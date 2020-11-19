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

	virtual ICharacter* clone(int id) = 0;
protected:
	int health = 0;
	bool canJump = false;
};