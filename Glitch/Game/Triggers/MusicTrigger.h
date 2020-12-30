#pragma once
#include "Game/Triggers/BaseTrigger.h"

/// @brief When triggered plays music
class MusicTrigger : public BaseTrigger
{
private:
	Level level;
	unique_ptr<Engine>& engine;
public:
	MusicTrigger(Level& _level, unique_ptr<Engine>& _engine, EventDispatcher& _dispatcher) : BaseTrigger(_dispatcher), engine(_engine), level(_level) { }
	MusicTrigger(const int _id, Level& _level, unique_ptr<Engine>& _engine, EventDispatcher& _dispatcher) : BaseTrigger(_id, _dispatcher), engine(_engine), level(_level) { }

	shared_ptr<BaseTrigger> clone(const int id) override { return shared_ptr<BaseTrigger>(new MusicTrigger(id, level, engine, dispatcher)); }

	void onUpdate(float deltaTime) override {}

	/// @brief Is called when a player collides with a music trigger
	/// @param event 
	/// @return 
	bool onCollisionBegin(const Event& event) override {
		auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne()->getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo()->getObjectId() != this->getObjectId()) return false;

		if (shared_ptr<Player> character = dynamic_pointer_cast<Player>(collisionEvent.getObjectOne())) {
			engine->loadSound("OPERA", "Assets/Sound/opera-vocals.wav");
			engine->startSound("OPERA");

		}
		else if (shared_ptr<Player> character = dynamic_pointer_cast<Player>(collisionEvent.getObjectTwo())) {
			engine->loadSound("OPERA", "Assets/Sound/opera-vocals.wav");
			engine->startSound("OPERA");
		}
		return false;
	}
};