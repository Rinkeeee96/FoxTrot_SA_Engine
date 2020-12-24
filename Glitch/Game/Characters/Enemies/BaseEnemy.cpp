#include "pch.h"
#include "BaseEnemy.h"

/// @brief
/// Checks if the enemy collides with anything and acts accordingly (dies if a player jumps on it, or remove player health for any other collision direction)
/// @param event
/// The actual collision event
/// @returns bool
bool BaseEnemy::onCollisionBeginEvent(const Event& event) {
	auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
	if (collisionEvent.getObjectOne()->getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo()->getObjectId() != this->getObjectId()) return false;

	auto map = collisionEvent.getDirectionMap();
	auto collidedDirection = map[this->getObjectId()];

	if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::UP) != collidedDirection.end()) {
		if (collisionEvent.getObjectOne()->getObjectId() == this->getObjectId()) {
			shared_ptr<Object> otherEntity = collisionEvent.getObjectTwo();

			if (this->player->getObjectId() == otherEntity->getObjectId()) {
				this->kill();
				int randomNumber = 1 + (rand() % static_cast<int>(5 - 1 + 1));
				this->player->inventory.coins += randomNumber;
			}
		}
		else if (collisionEvent.getObjectTwo()->getObjectId() == this->getObjectId()) {
			shared_ptr<Object> otherEntity = collisionEvent.getObjectOne();

			if (this->player->getObjectId() == otherEntity->getObjectId()) {
				this->kill();
				int randomNumber = 1 + (rand() % static_cast<int>(5 - 1 + 1));
				this->player->inventory.coins += randomNumber;
			}
		}
	}
	else {
		if (collisionEvent.getObjectOne()->getObjectId() == this->getObjectId()) {
			shared_ptr<Object> otherEntity = collisionEvent.getObjectTwo();

			if (this->player->getObjectId() == otherEntity->getObjectId()) {
				this->doDamage();
			}
		}
		else if (collisionEvent.getObjectTwo()->getObjectId() == this->getObjectId()) {
			shared_ptr<Object> otherEntity = collisionEvent.getObjectOne();

			if (this->player->getObjectId() == otherEntity->getObjectId()) {
				this->doDamage();
			}
		}
	}
	return false;
}