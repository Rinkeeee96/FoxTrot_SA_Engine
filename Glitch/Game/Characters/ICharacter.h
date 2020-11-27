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

	float getSpawnX() const { this->spawnX; }
	void setSpawnX(float val) { this->spawnX = val; }

	float getSpawnY() const { this->spawnY; }
	void setSpawnY(float val) { this->spawnY = val; }

	int getHealth() const { this->health; }
	void setHealth(int val) { this->health = val; }
	void removeHealth(int val) { 
		this->health -= val;
		if (this->health <= 0) {
			this->kill();
		}
	}

	void kill() { this->health = 0; }
	void respawn() { this->setPositionX(spawnX); this->setPositionY(spawnY); }
	bool getIsDead() const { return this->health == 0; }

	virtual ICharacter* clone(int id) = 0;
protected:
	int health = 0;
	bool canJump = false;
	float spawnX = 0;
	float spawnY = 0;
};