#include "stdafx.h"
#include "ContactListenerAdapter.h"

/// @brief 
/// Fires Event when a contact between two objects begin
/// @overrides box2dContactListener
void ContactListenerAdapter::BeginContact(b2Contact* contact) {
	b2Fixture* fixtureOne = contact->GetFixtureA();
	b2Fixture* fixtureTwo = contact->GetFixtureB();
	auto result = facade->getObjectsByFixture(fixtureOne, fixtureTwo);
	if (result.object1 != nullptr && result.object2 != nullptr) {
		map<int, vector<Direction>> direction = getCollisionDirection(result);

		dispatcher.dispatchEvent<OnCollisionBeginEvent>((Event&)OnCollisionBeginEvent(result.object1->getObject(), result.object2->getObject(), direction));
	}
}

/// @brief This function gets te direction of the collision.
/// @param result 
/// @return 
map<int, vector<Direction>> ContactListenerAdapter::getCollisionDirection(CollisionStruct result) {
	map<int, vector<Direction>> direction;
	auto object1minY = result.object1->getPositionY();
	auto object1minX = result.object1->getPositionX();
	auto object1maxY = result.object1->getPositionY() + result.object1->getHeight();
	auto object1maxX = result.object1->getPositionX() + result.object1->getWidth();

	auto object2minY = result.object2->getPositionY();
	auto object2minX = result.object2->getPositionX();
	auto object2maxY = result.object2->getPositionY() + result.object2->getHeight();
	auto object2maxX = result.object2->getPositionX() + result.object2->getWidth();

	Rectangle left{ object1minX * 32 - 10.0f, object1minY * 32 - result.object1->getHeight() * 32 + 5.0f, 10.0f, result.object1->getHeight() * 32 - 10.0f };
	Rectangle right{ object1maxX * 32 , object1minY * 32 - result.object1->getHeight() * 32 + 5.0f, 10.0f, result.object1->getHeight() * 32 - 10.0f };

	Rectangle top{ object1minX * 32 + 5.0f, object1minY * 32 - result.object1->getHeight() * 32 - 10.0f, result.object1->getWidth() * 32 - 10.0f, 10.0f };
	Rectangle bottom{ object1minX * 32 + 5.0f, object1maxY * 32 - result.object1->getHeight() * 32 , result.object1->getWidth() * 32 - 10.0f, 10.0f };

	Rectangle objectRectangle{ result.object2->getPositionX() * 32, result.object2->getPositionY() * 32 - result.object2->getHeight() * 32 , result.object2->getWidth() * 32, result.object2->getHeight() * 32 };

	auto collisionTop = top.overlaps(objectRectangle);
	auto collisionBottom = bottom.overlaps(objectRectangle);
	auto collisionLeft = left.overlaps(objectRectangle);
	auto collisionRight = right.overlaps(objectRectangle);

	auto obj1 = vector<Direction>();
	auto obj2 = vector<Direction>();
	if (collisionTop) {
		obj1.push_back(Direction::UP);
		obj2.push_back(Direction::DOWN);
	}
	if (collisionBottom) {
		obj1.push_back(Direction::DOWN);
		obj2.push_back(Direction::UP);
	}
	if (collisionLeft) {
		obj1.push_back(Direction::LEFT);
		obj2.push_back(Direction::RIGHT);
	}
	if (collisionRight) {
		obj1.push_back(Direction::RIGHT);
		obj2.push_back(Direction::LEFT);
	}
	direction.insert(pair<int, vector<Direction>>(result.object1->getObjectId(), obj1));
	direction.insert(pair<int, vector<Direction>>(result.object2->getObjectId(), obj2));
	return direction;
}

/// @brief 
/// Fires Event when a contact between two objects end
/// @overrides box2dContactListener
void ContactListenerAdapter::EndContact(b2Contact* contact) {
	b2Fixture* fixtureOne = contact->GetFixtureA();
	b2Fixture* fixtureTwo = contact->GetFixtureB();

	auto result = facade->getObjectsByFixture(fixtureOne, fixtureTwo);
	if (result.object1 != nullptr && result.object2 != nullptr) {
		map<int, vector<Direction>> direction = getCollisionDirection(result);

		dispatcher.dispatchEvent<OnCollisionEndEvent>((Event&)OnCollisionEndEvent(result.object1->getObject(), result.object2->getObject(), direction));
	}
};

