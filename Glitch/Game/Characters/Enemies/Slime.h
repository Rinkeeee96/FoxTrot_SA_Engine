#pragma once
#include "Game/Characters/Enemies/IEnemy.h"

//TODO Use deltaTime
#define JUMP_ANIMATION_TIME 50

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
		bool positionedOnGround = this->getYAxisVelocity() == 0;
		float slimeMiddleX = this->getPositionX() + (this->getWidth() / 2);
		bool playerIsBelowMe = this->getPositionY() < player->getPositionY();
		bool playerIsOnSameXLvl = (slimeMiddleX >= player->getPositionX()) && (slimeMiddleX <= (player->getPositionX() + player->getWidth()));

		if (positionedOnGround && !jumping) {
			jumping = true;
		}

		if (playerIsBelowMe && playerIsOnSameXLvl) {
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::DOWN, this->getObjectId()));
		}

		if (jumping) {
			jumpTimer++;
			if (jumpTimer < JUMP_ANIMATION_TIME / 2) {
				changeToState(SpriteState::ACTION_2);
			}
			if (jumpTimer == JUMP_ANIMATION_TIME / 2) {
				changeToState(SpriteState::ACTION_1);
			}
			if (jumpTimer == JUMP_ANIMATION_TIME) {
				changeToState(SpriteState::ACTION_3);
				dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
				jumpTimer = 0;
				jumping = false;
			}
		}
	};

	map<SpriteState, SpriteObject*> buildSpritemap(int startId) override {
		std::map<SpriteState, SpriteObject*> spriteMap;

		auto slimeDefault = new SpriteObject(startId++, 23, 31, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_idle.png");
		auto slimeAction1 = new SpriteObject(startId++, 24, 33, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_action1.png");
		auto slimeAction2 = new SpriteObject(startId++, 24, 33, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_action2.png");
		auto slimeAction3 = new SpriteObject(startId++, 24, 33, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_action3.png");

		spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::DEFAULT, slimeDefault));
		spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_1, slimeAction1));
		spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_2, slimeAction2));
		spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_3, slimeAction3));

		return spriteMap;
	}

	ICharacter* clone(int id) override { return new Slime(id, this->dispatcher); }

private:
	int jumpTimer = 0;
	bool jumping = false;
};