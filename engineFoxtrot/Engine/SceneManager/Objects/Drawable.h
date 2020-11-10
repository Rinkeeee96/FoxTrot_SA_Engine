#pragma once
#include "SceneManager/Objects/Object.h"
#include <Events\EventSingleton.h>
#include <Events\Video\VideoLoadSpriteEvent.h>
class API Drawable : public Object
{
public:
	Drawable(const int _id, const bool _isParticle = false) : Object(_id), isParticle(_isParticle) {};

	/// @brief
	/// get the current active sprite reference of the drawable
	SpriteObject& GetCurrentSprite() const { return *currentSprite; }

	/// @brief
	/// register a new state or overwrite a existing state
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


	bool getIsParticle() { return isParticle; }

protected:
	// TODO	particle related things
	const bool isParticle = false;

	SpriteObject* currentSprite = nullptr;
	map<const int, SpriteObject*> textures;
};

