#include "pch.h"
#include "Slime.h"

/// @brief
/// Checks if the player is within range and acts accordingly
/// The Slime will jump if it is on the ground
/// If the player is below the Slime, it will add a downwards velocity to reach the player faster
void Slime::onUpdate() {
	bool positionedOnGround = this->getYAxisVelocity() == 0;
	float slimeMiddleXPosition = this->getPositionX() + (this->getWidth() / 2);
	bool playerIsLowerThanMe = this->getPositionY() < player->getPositionY();
	bool playerIsWithinXLevelRange = (slimeMiddleXPosition >= player->getPositionX()) && (slimeMiddleXPosition <= (player->getPositionX() + player->getWidth()));

	if (positionedOnGround && !jumping) {
		jumping = true;
	}

	if (playerIsLowerThanMe && playerIsWithinXLevelRange) {
		dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::DOWN, this->getObjectId()));
	}

	if (jumping) {
		jumpTimer++;
		if (jumpTimer < SLIME_JUMP_ANIMATION_TIME / 2) {
			changeToState(SpriteState::ACTION_2);
		}
		else if (jumpTimer == SLIME_JUMP_ANIMATION_TIME / 2) {
			changeToState(SpriteState::ACTION_1);
		}
		else if (jumpTimer == SLIME_JUMP_ANIMATION_TIME) {
			changeToState(SpriteState::ACTION_3);
			dispatcher.dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getObjectId()));
			jumpTimer = 0;
			jumping = false;
		}
	}
}

/// @brief
/// Builds the spritemap for the Slime
map<SpriteState, SpriteObject*> Slime::buildSpritemap(int textureId) {
	std::map<SpriteState, SpriteObject*> spriteMap;

	auto slimeDefault = new SpriteObject(textureId++, SLIME_IDLE_SPRITE_HEIGHT, SLIME_IDLE_SPRITE_WIDTH, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_default.png");
	auto slimeAction1 = new SpriteObject(textureId++, SLIME_ACTION_SPRITE_HEIGHT, SLIME_ACTION_SPRITE_WIDTH, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_action_1.png");
	auto slimeAction2 = new SpriteObject(textureId++, SLIME_ACTION_SPRITE_HEIGHT, SLIME_ACTION_SPRITE_WIDTH, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_action_2.png");
	auto slimeAction3 = new SpriteObject(textureId++, SLIME_ACTION_SPRITE_HEIGHT, SLIME_ACTION_SPRITE_WIDTH, 1, 200, "Assets/Sprites/Enemies/Slime/Slime_action_3.png");

	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::DEFAULT, slimeDefault));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_1, slimeAction1));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_2, slimeAction2));
	spriteMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::ACTION_3, slimeAction3));

	return spriteMap;
}