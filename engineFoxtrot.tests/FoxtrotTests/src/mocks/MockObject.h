#pragma once
#include <Engine/SceneManager/Objects/Object.h>

class MockObject : public Object {
public:
	MockObject() : Object(1, false) { }
	void onUpdate() override { }
};