#pragma once
#include <Engine/SceneManager/Objects/Object.h>

class MockObject : public Object {
public:
	MockObject() : Object(1, false) { }
	void onUpdate(float deltaTime) override { }
};

class MockDrawable : public Drawable {
public:
	MockDrawable() : Drawable(2, false) { }
	void onUpdate(float deltaTime) override { }
};