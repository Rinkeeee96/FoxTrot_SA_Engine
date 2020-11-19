#pragma once
#include "SceneManager/Objects/Object.h"
#include <Events\EventSingleton.h>
#include <Events\Video\VideoLoadSpriteEvent.h>
#include "Structs/HelperStructs.h"
class API Drawable : public Object
{
public:
	Drawable(const int _id, const bool _isParticle = false) : Object(_id, _isParticle) {};

	/// @brief
	/// get the current active sprite reference of the drawable
	SpriteObject& GetCurrentSprite() const { return *currentSprite; }

	/// @brief
	/// register a new state or overwrite a existing state and dispatch an event that signals to load the sprite in memory
	/// register the spriteID
	/// link a state with a sprite
	void registerSprite(int state, SpriteObject* spriteObject) {
		textures.insert(pair<int, SpriteObject*>(state, spriteObject));
		EventSingleton::get_instance().dispatchEvent<VideoLoadSpriteEvent>((Event&)VideoLoadSpriteEvent(*spriteObject));
	}
	/// @brief
	/// change the state
	/// change the textureID to the current state
	void changeToState(const int state) {
		SpriteObject* spriteObject = textures[state];
		if (spriteObject == nullptr) throw ERROR_CODE_SPRITE_DOESNT_EXIST;
		this->currentSprite = spriteObject;
	}
	virtual const ColoredText* toString() { return nullptr; }

protected:
	// TODO	particle related things

	SpriteObject* currentSprite = nullptr;
	map<const int, SpriteObject*> textures;
};

