#pragma once
#include "Game/SpriteState.h"
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/Scenes.h"

/// @brief 
/// Game class runs the game
class Game
{
public:
	Game();
	void run();
	bool stopRun(Event& event);

	int sceneIdentifierToID(string& identifier);
	void switchToScene(string const identifier, bool useTransitionScreen);

private:
	Engine engine;

	map<string, Scene*> scenes;
	bool currentlyRunningTransition = false;

	void registerScene(string const identifier, Scene* scene) { 
		if (scene == nullptr) throw exception("Scene is nullptr");

		if (dynamic_cast<GameScene*>(scene))
		{
			cout << "Registered Game" << endl;
			((GameScene*)scene)->registerGame(this);
		}

		engine.insertScene(scene);
		scenes.insert(pair<string, Scene*>(identifier, scene));
	}

	void registerTransitionScene(Scene* scene)
	{
		if (dynamic_cast<GameScene*>(scene))
		{
			cout << "Registered Game" << endl;
			((GameScene*)scene)->registerGame(this);
		}
		registerScene("GENERAL_TRANSITION_SCENE", scene);
	}

	

	Scene * currentScene;
	bool gameRunning = true;
	int sceneId = 0;
};

