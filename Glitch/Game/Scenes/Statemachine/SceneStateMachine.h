#pragma once
#include "Game/Scenes/Factory/FactoryMethod.h"
#include "Game/Scenes/Scenes.h"
#include "Game/Scenes/Factory/CreatorImpl.h"
class Savegame;

class SceneStateMachine
{
public:
	SceneStateMachine(Engine& engine, Savegame* savegame);
	~SceneStateMachine();

	void switchToScene(string const identifier, bool useTransitionScreen);

	void updateCurrentScene()
	{
		if (currentScene)currentScene->onUpdate();
	}

private:

	shared_ptr<SceneFactory>  factory = nullptr;

	Engine& engine;
	Savegame* savegame;

	unique_ptr<Scene> currentScene;
	int sceneId = 0;
};

