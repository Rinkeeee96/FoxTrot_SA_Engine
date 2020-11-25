#pragma once
#include "Game/Scenes/Factory/FactoryMethod.h"
#include "Game/Scenes/Scenes.h"
#include "Game/Scenes/Factory/CreatorImpl.h"

class SceneStateMachine
{
public:
	SceneStateMachine();
	~SceneStateMachine();

	void registerEngine(shared_ptr<Engine> engine) { this->engine = engine; };

	void switchToScene(string const identifier, bool useTransitionScreen);

	void updateCurrentScene()
	{
		if (currentScene)currentScene->onUpdate();
	}

private:
	Factory *factory = nullptr;

	shared_ptr<Engine> engine;
	shared_ptr<Scene> currentScene;
	int sceneId = 0;

};

