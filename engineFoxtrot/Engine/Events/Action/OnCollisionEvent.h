#pragma once
#include "Events/Event.h"
#include "Events/Action/ActionEvent.h"
#include "SceneManager/Objects/Object.h"

/// @brief
/// OnCollisionEvent base class of CollisionEnd and CollisionStart
class OnCollisionEvent : public Event
{
public:
	API OnCollisionEvent(Object& _objectOne, Object& _objectTwo, const map<int, vector<Direction>> _directionMap) :
		objectOne{ _objectOne },
		objectTwo{ _objectTwo },
		directionMap{ _directionMap }{};

	/// @brief
	/// The id of one of the objects where collision happend
	API Object& GetObjectOne() const { return objectOne; }
	/// @brief
	/// The id of one of the objects where collision happend
	API Object& GetObjectTwo() const { return objectTwo; }
	/// @brief
	/// Returns the eventType of a specific event
	/// @return EventType
	API virtual EventType GetEventType() const override = 0;
	/// @brief
	/// Returns the name of the event
	API virtual const char* GetName() const override = 0;

	API map<int, vector<Direction>> getDirectionMap() { return directionMap; };
protected:
	Object& objectOne;
	Object& objectTwo;
	map<int, vector<Direction>> directionMap;
};

/// @brief
/// OnCollisionEvent is fired when a a collision ended
class OnCollisionEndEvent : public OnCollisionEvent {
public:
	API OnCollisionEndEvent(Object& _objectOne, Object& _objectTwo, const map<int, vector<Direction>> _directionMap)
		: OnCollisionEvent(_objectOne, _objectTwo, _directionMap) {};

	API virtual const char* GetName() const override { return "Collision end Event"; }
	API EventType GetEventType() const override { return EventType::CollisionEnd; }
};

/// @brief
/// OnCollisionEvent is fired when a a collision started
class OnCollisionBeginEvent : public OnCollisionEvent {
public:
	API OnCollisionBeginEvent(Object& _objectOne, Object& _objectTwo, const map<int, vector<Direction>> _directionMap)
		: OnCollisionEvent(_objectOne, _objectTwo, _directionMap) {};

	API virtual const char* GetName() const override { return "Collision begin Event"; }
	API virtual EventType GetEventType() const override { return EventType::CollisionBegin; }
};