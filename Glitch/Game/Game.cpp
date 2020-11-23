#include "pch.h"
#include "Game.h"

bool Game::stopRun(Event& event) {
	gameRunning = false;
	return true;
}

Game::Game()
{
}

void Game::switchToScene(string const identifier, bool useTransitionScreen) {
	if (DEBUG_MAIN) { useTransitionScreen = false; }

	auto scene = scenes.find(identifier);
	if (scene == scenes.end())
		throw exception("Scene is end()");
	//TODO start transitiescreen

	auto transScene = scenes.find("GENERAL_TRANSITION_SCENE");
	bool transitionSceneAvailable = true;
	transScene == scenes.end() ? transitionSceneAvailable = false : transitionSceneAvailable = true;

	if (!currentlyRunningTransition && useTransitionScreen && transitionSceneAvailable)
	{
		currentlyRunningTransition = true;
		engine.setCurrentScene(scenes["GENERAL_TRANSITION_SCENE"]->getSceneID());
		scene = scenes.find("GENERAL_TRANSITION_SCENE");
		((GeneralTransition*)scene->second)->setNextScene(identifier);
	}
	else
	{
		engine.setCurrentScene(scene->second->getSceneID());
		currentlyRunningTransition = false;
	}

	cout << "Setting current Scene to: " << engine.getCurrentScene()->getSceneID() << endl;

	// Detach the old now inactive scene
	if (currentScene != nullptr)
	{
		currentScene->onDetach();
	}

	scene->second->onAttach();
	scene->second->start();

	// Set the new scene active
	currentScene = scene->second;

	
}

void Game::run() {
	try {
		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));

		MainMenu* mainMenu = new MainMenu(sceneId++);
		mainMenu->registerGame(this);
		registerScene("MAIN_MENU", mainMenu);

		GeneralTransition* generalTransitionScene = new GeneralTransition(sceneId++);
		registerScene("GENERAL_TRANSITION_SCENE", generalTransitionScene);
		generalTransitionScene->registerGame(this);
		
		Overworld* overWorld = new Overworld(sceneId++);
		registerScene("OVERWORLD", overWorld);
		overWorld->registerGame(this);

		DeadScreen* deadScreen = new DeadScreen(sceneId++);
		registerScene("DEAD_SCREEN", deadScreen);
		deadScreen->registerGame(this);

		WinScreen* winScreen = new WinScreen(sceneId++);
		registerScene("WIN_SCREEN", winScreen);
		winScreen->registerGame(this);

		SaveScreen* saveScreen = new SaveScreen(sceneId++);
		registerScene("LOADSCREEN", saveScreen);
		saveScreen->registerGame(this);

		switchToScene("MAIN_MENU",false);
		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));
	}
	catch (exception e) {
		cout << e.what() << endl;
		return;
	}

	LoadLevelFacade levelLoader{ engine };
	LevelBuilder levelOneBuilder{ engine, sceneId++ };
	try {
		levelLoader.load("Assets/Levels/Maps/Level1.json", &levelOneBuilder);
		auto level = levelOneBuilder.getLevel();
		registerScene("LEVEL_1", level);
		level->registerGame(this);
	}
	catch (exception e) {
		cout << e.what() << endl;
		return;
	}

	try {
		while (gameRunning)
		{
			AppTickEvent60 appTick;
			AppTickEvent30 appTick30;

			engine.pollEvents();
			EventSingleton::get_instance().dispatchEvent<AppTickEvent60>(appTick);
			EventSingleton::get_instance().dispatchEvent<AppTickEvent30>(appTick30);

			// TODO get only the non static objects, without looping thru them again and again
			if(currentScene)currentScene->onUpdate();

			this_thread::sleep_for(chrono::milliseconds(10));
		}

		Savegame::get_instance().saveGameDataToJsonFile();

	}
	catch (int e) {
		cout << ERRORCODES[e] << endl;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}
