#include "pch.h"
#include "BaseEnemy.h"

/// @brief
/// Checks if the enemy collides with anything and acts accordingly (dies if a player jumps on it, or remove player health for any other collision direction)
/// @param event
/// The actual collision event
/// @returns bool
bool BaseEnemy::onCollisionBeginEvent(const Event& event) {
	auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
	if (collisionEvent.getObjectOne().getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo().getObjectId() != this->getObjectId()) return false;

	auto map = collisionEvent.getDirectionMap();
	auto collidedDirection = map[this->getObjectId()];

	if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::UP) != collidedDirection.end()) {
		this->kill();
	}
	else {
		if (collisionEvent.getObjectOne().getObjectId() == this->getObjectId()) {
			Object& otherEntity = collisionEvent.getObjectTwo();

			if (this->player->getObjectId() == otherEntity.getObjectId()) {
				this->doDamage();
			}
		}
		else if (collisionEvent.getObjectTwo().getObjectId() == this->getObjectId()) {
			Object& otherEntity = collisionEvent.getObjectOne();

			if (this->player->getObjectId() == otherEntity.getObjectId()) {
				this->doDamage();
			}
		}
	}
	return false;
}