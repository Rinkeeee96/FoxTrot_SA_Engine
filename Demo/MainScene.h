#pragma once
#include "DynamicObject.h"
#include "SpriteState.h"

class MainScene : public Scene
{
public:
	MainScene(Engine& _engine) : Scene(1, 1080, 1920), engine{ _engine } {

	}

	void loadScene();

	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	void onUpdate() override;

	Engine& engine;
};