#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

/// @brief 
/// Slime class with correspondending AI logic
class Slime : public IEnemy {
public:
	Slime(EventDispatcher& _dispatcher) : IEnemy(_dispatcher) {}
	Slime(const int id, EventDispatcher& _dispatcher) : IEnemy(id, _dispatcher) {
		_dispatcher.setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Slime::onCollisionBeginEvent));
	}

	bool onCollisionBeginEvent(const Event& event) {
		auto collisionEvent = static_cast<const OnCollisionBeginEvent&>(event);
		if (collisionEvent.getObjectOne().getObjectId() != this->getObjectId() && collisionEvent.getObjectTwo().getObjectId() != this->getObjectId()) return false;

		auto map = collisionEvent.getDirectionMap();
		auto collidedDirection = map[this->getObjectId()];

		if (std::find(collidedDirection.begin(), collidedDirection.end(), Direction::UP) != collidedDirection.end()) {
			this->kill();
		}
		else {
			if (collisionEvent.getObjectOne().getObjectId() == this->getObjectId()) {
				Object& otherE = collisionEvent.getObjectTwo();

				if (this->player->getObjectId() == otherE.getObjectId()) {
					this->player->setCurrentHealth(this->player->getCurrentHealth() - 1);
				}
			}
			else if (collisionEvent.getObjectTwo().getObjectId() == this->getObjectId()) {
				Object& otherEntity = collisionEvent.getObjectOne();

				if (this->player->getObjectId() == otherEntity.getObjectId()) {
					this->player->setCurrentHealth(this->player->getCurrentHealth() - 1);
				}
			}
		}
		return false;
	}

	void onUpdate() override {
		bool playerIsInRange = player->getPositionX() >= this->getPositionX() - this->getWidth() &&
			player->getPositionX() <= this->getPositionX() + this->width;
		bool playerIsBelowMe = (player->getPositionY() + player->getHeight()) >= this->getPositionY();

		bool positionedOnGround = this->getYAxisVelocity() == 0;
		if(positionedOnGround)
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));

		if (playerIsInRange && playerIsBelowMe && !positionedOnGround){
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::DOWN, this->getObjectId()));
		}
	};

	map<SpriteState, SpriteObject*> buildSpritemap(int startId) override {
		std::map<SpriteState, SpriteObject*> spriteMap;

		auto slimeDefault = new SpriteObject(startId, 16, 16, 1, 200, "Assets/Levels/Tiles/slime_blue.png");

		spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::DEFAULT, slimeDefault));

		return spriteMap;
	}

	ICharacter* clone(int id) override { return new Slime(id, this->dispatcher); }
};