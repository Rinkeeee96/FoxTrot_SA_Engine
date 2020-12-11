#pragma once
#include "SceneManager/Objects/Object.h"
#include "Structs/HelperStructs.h"
class Drawable : public Object
{
public:
	API Drawable(const int _id, const bool _isParticle = false) : Object(_id, _isParticle) {};
	API Drawable() : Object() {};

	API virtual ~Drawable() override {
		Object::~Object();
	};
	/// @brief
	/// get the current active sprite reference of the drawable
	API SpriteObject& GetCurrentSprite() const { return *currentSprite; }

	/// @brief
	/// register a new state or overwrite a existing state and dispatch an event that signals to load the sprite in memory
	/// register the spriteID
	/// link a state with a sprite
	API virtual void registerSprite(int state, SpriteObject* spriteObject) {
		textures.insert(pair<int, SpriteObject*>(state, spriteObject));
	}
	/// @brief
	/// change the state
	/// change the textureID to the current state
	API virtual void changeToState(const int state) {
		currentSpriteState = state;
		SpriteObject* spriteObject = textures[state];
		if (spriteObject == nullptr) throw ERROR_CODE_SPRITE_DOESNT_EXIST;
		this->currentSprite = spriteObject;
	}

	API virtual const ColoredText* toString() { return nullptr; }

	virtual void onUpdate(float deltaTime) override { }
	API virtual void setTint(int r, int g, int b) { this->tint = Color{ r, g, b }; }
	API virtual void removeTint() { this->tint = Color{ 255, 255, 255 };}
	API virtual Color getTint() { return this->tint; }

	bool getIsText() const { return this->isText; }

	bool getDrawStatic() { return this->drawStatic; }
	void setDrawStatic(bool val) { this->drawStatic = val; }
protected:
	// TODO	particle related things
	bool isText = false;
	Color tint{ 255, 255, 255 };
protected:
	// TODO	particle related things
	bool drawStatic = false;
	int currentSpriteState = 0;
	SpriteObject* currentSprite = nullptr;
	// TODO delete on scene detach in destructor when object is destroyed
	map<const int, SpriteObject*> textures;
};

class Text : public Drawable {
private:
	ColoredText* color = nullptr;
public:
	Text(const int _id, ColoredText* _color, float _width, float _height, float _x, float _y)
		: color(_color), Drawable(_id)
	{
		Object::setHeight(_height);
		Object::setWidth(_width);
		Object::setPositionX(_x);
		Object::setPositionY(_y);

		this->isText = true;
	}

	~Text() {
		delete color;
	}

	API virtual const ColoredText* toString() { return color; }
};

