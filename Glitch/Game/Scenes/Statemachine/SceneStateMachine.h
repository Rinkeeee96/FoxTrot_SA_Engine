#pragma once
#include "Game/Scenes/Factory/FactoryMethod.h"
#include "Game/Scenes/Scenes.h"
#include "Game/Scenes/Factory/CreatorImpl.h"

class SceneStateMachine
{
public:
	SceneStateMachine(Engine& engine);
	~SceneStateMachine();

	void switchToScene(string const identifier, bool useTransitionScreen);

	void updateCurrentScene()
	{
		if (currentScene)currentScene->onUpdate();
	}

private:

	shared_ptr<SceneFactory>  factory = nullptr;

	Engine& engine;
	shared_ptr<Scene> currentScene;
	int sceneId = 0;

};
