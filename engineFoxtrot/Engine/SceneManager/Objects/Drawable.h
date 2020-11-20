#pragma once
#include "SceneManager/Objects/Object.h"
#include "Events\EventSingleton.h"
#include "Events\Video\VideoLoadSpriteEvent.h"
#include "Structs/HelperStructs.h"
class Drawable : public Object
{
public:
	API Drawable(const int _id, const bool _isParticle = false) : Object(_id, _isParticle) {};
	API Drawable() : Object() {};

	API virtual ~Drawable() {};
	/// @brief
	/// get the current active sprite reference of the drawable
	API SpriteObject& GetCurrentSprite() const { return *currentSprite; }

	/// @brief
	/// register a new state or overwrite a existing state and dispatch an event that signals to load the sprite in memory
	/// register the spriteID
	/// link a state with a sprite
	API void registerSprite(int state, SpriteObject* spriteObject) {
		textures.insert(pair<int, SpriteObject*>(state, spriteObject));
		EventSingleton::get_instance().dispatchEvent<VideoLoadSpriteEvent>((Event&)VideoLoadSpriteEvent(*spriteObject));
	}
	/// @brief
	/// change the state
	/// change the textureID to the current state
	API void changeToState(const int state) {
		currentSpriteState = state;
		SpriteObject* spriteObject = textures[state];
		if (spriteObject == nullptr) throw ERROR_CODE_SPRITE_DOESNT_EXIST;
		this->currentSprite = spriteObject;
	}

	API virtual const ColoredText* toString() { return nullptr; }

	virtual void onUpdate() override {

	}

protected:
	// TODO	particle related things

	int currentSpriteState = 0;
	SpriteObject* currentSprite = nullptr;
	map<const int, SpriteObject*> textures;
};

