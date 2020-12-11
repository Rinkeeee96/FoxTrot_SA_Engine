#pragma once
#include "Game/Triggers/BaseTrigger.h"

class WinTrigger : public BaseTrigger
{
private:
	Level& level;
public:
	WinTrigger(Level& _level, EventDispatcher& _dispatcher) : BaseTrigger(_dispatcher), level(_level) { }
	WinTrigger(const int _id, Level& _level, EventDispatcher& _dispatcher) : BaseTrigger(_id, _dispatcher), level(_level) { }

	BaseTrigger* clone(const int id) override { return new WinTrigger(id, level, dispatcher); }

	void onUpdate() override {}

	/// @brief Is called when a player collides with a win trigger
	/// @param event 
	/// @return 
	bool onCollisionBegin(const Event& event) override {
		auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne().getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo().getObjectId() != this->getObjectId()) return false;

		if (Player* characterObject = dynamic_cast<Player*>(&collisionEvent.getObjectOne())) this->level.setWin(true);
		else if (Player* characterObject = dynamic_cast<Player*>(&collisionEvent.getObjectTwo())) this->level.setWin(true);
		return false;
	}
};