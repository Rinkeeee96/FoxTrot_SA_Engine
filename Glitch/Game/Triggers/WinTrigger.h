#pragma once
#include "Game/Triggers/TriggerBase.h"

class WinTrigger : public TriggerBase
{
private:
	Level& level;
public:
	WinTrigger(Level& _level) : TriggerBase(), level(_level) { }
	WinTrigger(const int _id, Level& _level) : TriggerBase(_id), level(_level) { }

	virtual TriggerBase* clone(const int id) override { return new WinTrigger(id, level); }

	void onUpdate() override {}

	virtual bool onCollisionBegin(Event& event) override {
		auto collisionEvent = static_cast<OnCollisionBeginEvent&>(event);
		if (collisionEvent.GetObjectOne().getObjectId() != this->getObjectId() && collisionEvent.GetObjectTwo().getObjectId() != this->getObjectId()) return false;

		if (Player* characterObject = dynamic_cast<Player*>(&collisionEvent.GetObjectOne())) this->level.setWin(true);
		else if (Player* characterObject = dynamic_cast<Player*>(&collisionEvent.GetObjectTwo())) this->level.setWin(true);
	}
};