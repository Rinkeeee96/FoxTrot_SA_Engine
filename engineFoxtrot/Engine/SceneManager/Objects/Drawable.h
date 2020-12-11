#pragma once
#include "SceneManager/Objects/Object.h"
#include "Structs/HelperStructs.h"
/// @brief Base class for all objects that can be drawn
class Drawable : public Object
{
public:
	API Drawable(const int _id, const bool _isParticle = false) : Object(_id, _isParticle) {};
	API Drawable() : Object() {};

	API virtual ~Drawable() override {
		Object::~Object();
	};

	API SpriteObject& GetCurrentSprite() const { return *currentSprite; }

	API virtual void registerSprite(int state, SpriteObject* spriteObject);
	API virtual void changeToState(const int state);

	API virtual const ColoredText* toString() { return nullptr; }

	API virtual void setTint(int r, int g, int b) { this->tint = Color{ r, g, b }; }
	API virtual void removeTint() { this->tint = Color{ 255, 255, 255 };}
	API virtual Color getTint() { return this->tint; }

	virtual void onUpdate() override { }

	bool getIsText() const { return this->isText; }

	bool getDrawStatic() { return this->drawStatic; }
	void setDrawStatic(bool val) { this->drawStatic = val; }
protected:
	// TODO	particle related things
	bool isText = false;
	Color tint{ 255, 255, 255 };
	bool drawStatic = false;
	int currentSpriteState = 0;
	SpriteObject* currentSprite = nullptr;

	// TODO delete on scene detach in destructor when object is destroyed
	map<const int, SpriteObject*> textures;
};

/// @brief Text class that should be drawn on the screen.
class Text : public Drawable {
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

private:
	ColoredText* color = nullptr;
};

