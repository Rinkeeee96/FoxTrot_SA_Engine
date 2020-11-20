#pragma once
#include "api.h"

/// @brief 
/// Gameobject base class
class IGameObject : public Drawable {
private:
	int startX = 0;
	int startY = 0;
public:
	IGameObject() : Drawable() {}
	IGameObject(const int id) : Drawable(id) {}
	virtual ~IGameObject() {}

	virtual void onUpdate() = 0;

	int getStartX() { return startX; }
	void setStartX(int i) { this->startX = i; }
	int getStartY() { return startY; }
	void setStartY(int i) { this->startY = i; }
};