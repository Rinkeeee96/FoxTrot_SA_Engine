#pragma once
#include <Engine/SceneManager/Scene.h>

class MockScene : public Scene {
public:
	MockScene() : Scene(1, 100, 100) { }
	void onAttach() override { }
	void start(bool playSound) override { }
	void onDetach() override { }
	void onUpdate() override { }
};
