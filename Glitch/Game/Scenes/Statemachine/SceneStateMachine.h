#pragma once
#include "Game/Scenes/Factory/FactoryMethod.h"
#include "Game/Scenes/Scenes.h"
#include "Game/Scenes/Factory/CreatorImpl.h"
class Savegame;

/// @brief Class for the scene state machine
class SceneStateMachine
{
public:
	SceneStateMachine(Engine& engine, shared_ptr<Savegame> savegame);
	~SceneStateMachine();

	void switchToScene(string const identifier, bool useTransitionScreen, bool playSound = true);

	void updateCurrentScene();

	string& getCurrentLevelIdentifier();

	int levelToBuild = 0;
private:

	shared_ptr<Savegame> savegame;
	shared_ptr<SceneFactory>  factory = nullptr;

	unique_ptr<Scene> loadLevel(const string& identifier);
	Engine& engine;

	unique_ptr<Scene> currentScene;
	int sceneId = 0;
	string currentLevelIdentifier = "";
};

