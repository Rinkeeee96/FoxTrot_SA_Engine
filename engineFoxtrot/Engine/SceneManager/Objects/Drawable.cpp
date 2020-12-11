#include "stdafx.h"
#include "Drawable.h"

/// @brief
/// register a new state or overwrite a existing state and dispatch an event that signals to load the sprite in memory
/// register the spriteID
/// link a state with a sprite
void Drawable::registerSprite(int state, SpriteObject* spriteObject)
{
	textures.insert(pair<int, SpriteObject*>(state, spriteObject));
}

/// @brief
/// change the state
/// change the textureID to the current state
void Drawable::changeToState(const int state)
{
	currentSpriteState = state;
	SpriteObject* spriteObject = textures[state];
	if (spriteObject == nullptr) throw ERROR_CODE_SPRITE_DOESNT_EXIST;
	this->currentSprite = spriteObject;
}

