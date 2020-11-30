#pragma once
#include "Game/IGameObject.h"
#include "Events/EventDispatcher.h"

/// @brief 
/// Character base class
class ICharacter : public IGameObject  {
public:
	ICharacter(shared_ptr<EventDispatcher> _dispatcher) : dispatcher{ _dispatcher } {};
	ICharacter(const int id, shared_ptr<EventDispatcher> _dispatcher) : dispatcher{ _dispatcher }, IGameObject(id) {}
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

	void kill() { this->health = 0; }
	bool getIsDead() const { return this->health == 0; }

	virtual ICharacter* clone(int id) = 0;

	void setDispatcher(shared_ptr<EventDispatcher> _dispatcher) { dispatcher = _dispatcher; }
protected:
	int health = 0;
	bool canJump = false;
	shared_ptr<EventDispatcher> dispatcher;
};