#include "pch.h"
#include "Game.h"

bool Game::stopRun(Event& event) {
	gameRunning = false;
	return true;
}

Game::Game()
{
}

int Game::sceneIdentifierToID(string& identifier)
{
	if (identifier == "MAIN_MENU") return 0x01;
	if (identifier == "GENERAL_TRANSITION_SCENE") return 0x02;
	if (identifier == "OVERWORLD") return 0x03;
	if (identifier == "DEAD_SCREEN") return 0x04;
	if (identifier == "WIN_SCREEN") return 0x05;
	if (identifier == "LOADSCREEN") return 0x06;
	if (identifier == "LEVEL_1") return 0x07;

	return 0;
}

void Game::switchToScene(string identifier, const bool _useTransitionScreen)
{
	bool useTransitionScreen = _useTransitionScreen;
	if (DEBUG_MAIN) { useTransitionScreen = false; }

	// Detach the old now inactive scene
	if (currentScene != nullptr)
	{
		currentScene->onDetach();
	}

	if (!currentlyRunningTransition && useTransitionScreen)
	{
		currentlyRunningTransition = true;
		GeneralTransition* generalTransitionScene = new GeneralTransition(sceneId++);
		engine.insertScene(generalTransitionScene);
		engine.setCurrentScene(generalTransitionScene->getSceneID());
		currentScene = generalTransitionScene;
		generalTransitionScene->setNextScene(identifier);
	}
	else
	{
		Scene* newScene = nullptr;
		switch (sceneIdentifierToID(identifier))
		{
		case 0x01:
		{
			MainMenu* mainMenu = new MainMenu(sceneId++);
			newScene = mainMenu;
			break;
		}
		case 0x02:
		{
			GeneralTransition* generalTransitionScene = new GeneralTransition(sceneId++);
			newScene = generalTransitionScene;
			break;
		}
		case 0x03:
		{
			Overworld* overWorld = new Overworld(sceneId++);
			newScene = overWorld;
			break;
		}
		case 0x04:
		{
			DeadScreen* deadScreen = new DeadScreen(sceneId++);
			newScene = deadScreen;
			break;
		}
		case 0x05:
		{
			WinScreen* winScreen = new WinScreen(sceneId++);
			newScene = winScreen;
			break;
		}
		case 0x06:
		{
			SaveScreen* saveScreen = new SaveScreen(sceneId++);
			newScene = saveScreen;
			break;
		}
		case 0x07:
			LoadLevelFacade levelLoader{ engine };
			LevelBuilder levelOneBuilder{ engine, sceneId++ };
			levelLoader.load("Assets/Levels/Maps/Level1.json", &levelOneBuilder);
			auto level = levelOneBuilder.getLevel();
			newScene = level;
			break;
		}

		engine.insertScene(newScene);
		engine.setCurrentScene(newScene->getSceneID());
		currentScene = newScene;
		currentlyRunningTransition = false;
	}

	if (currentScene && dynamic_cast<GameScene*>(currentScene))
	{
		((GameScene*)currentScene)->registerGame(this);
	}

	cout << "Setting current Scene to: " << engine.getCurrentScene()->getSceneID() << endl;

	currentScene->onAttach();
	currentScene->start();

}

void Game::run() {
	try {
		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));

		switchToScene("MAIN_MENU",false);
		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));
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
