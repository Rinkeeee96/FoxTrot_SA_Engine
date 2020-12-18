#pragma once
#include "Events/Event.h"
#include "Events/Action/ActionEvent.h"
#include "SceneManager/Objects/Object.h"

/// @brief
/// OnCollisionEvent base class of CollisionEnd and CollisionStart
class OnCollisionEvent : public Event
{
public:
	API OnCollisionEvent(shared_ptr<Object> _objectOneId, shared_ptr<Object> _objectTwoId, const map<int, vector<Direction>> _directionMap) :
		objectOneId{ _objectOneId }, 
		objectTwoId{ _objectTwoId }, 
		directionMap{ _directionMap }{};

	/// @brief
	/// The id of one of the objects where collision happend
	API shared_ptr<Object> getObjectOne() const { return objectOneId; }

	/// @brief
	/// The id of one of the objects where collision happend
	API shared_ptr<Object> getObjectTwo() const { return objectTwoId; }

	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	API virtual EventType getEventType() const override = 0;

	/// @brief
	/// Returns the name of the event
	API virtual const char* getName() const override = 0;

	API map<int, vector<Direction>> getDirectionMap() { return directionMap; };
protected:
	shared_ptr<Object> objectOneId;
	shared_ptr<Object> objectTwoId;
	map<int, vector<Direction>> directionMap;
};

/// @brief
/// OnCollisionEvent is fired when a a collision ended
class OnCollisionEndEvent : public OnCollisionEvent {
public:
	API OnCollisionEndEvent(shared_ptr<Object> _objectOneId, shared_ptr<Object> _objectTwoId, const map<int, vector<Direction>> _directionMap)
		: OnCollisionEvent(_objectOneId, _objectTwoId, _directionMap) {};

	API virtual const char* getName() const override { return "Collision end Event"; }
	API EventType getEventType() const override { return EventType::CollisionEnd; }
};

/// @brief
/// OnCollisionEvent is fired when a a collision started
class OnCollisionBeginEvent : public OnCollisionEvent {
public:
	API OnCollisionBeginEvent(shared_ptr<Object> _objectOneId, shared_ptr<Object> _objectTwoId, const map<int, vector<Direction>> _directionMap)
		: OnCollisionEvent(_objectOneId, _objectTwoId, _directionMap) {};

	API virtual const char* getName() const override { return "Collision begin Event"; }
	API virtual EventType getEventType() const override { return EventType::CollisionBegin; }
};