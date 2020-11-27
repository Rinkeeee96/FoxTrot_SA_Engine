#include "pch.h"
#include "Game.h"

bool Game::stopRun(Event& event) {
	gameRunning = false;
	return true;
}

Game::Game()
{
	SceneSwitcher::get_instance().setEngine(&engine);
}

int Game::run() {
	try {
		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));

		MainMenu* mainMenu = new MainMenu(sceneId++);
		SceneSwitcher::get_instance().registerScene("MAIN_MENU", mainMenu);

		GeneralTransition* generalTransitionScene = new GeneralTransition(sceneId++);
		SceneSwitcher::get_instance().registerScene("GENERAL_TRANSITION_SCENE", generalTransitionScene);
		
		Overworld* overWorld = new Overworld(sceneId++);
		SceneSwitcher::get_instance().registerScene("OVERWORLD", overWorld);

		DeadScreen* deadScreen = new DeadScreen(sceneId++);
		SceneSwitcher::get_instance().registerScene("DEAD_SCREEN", deadScreen);

		WinScreen* winScreen = new WinScreen(sceneId++);
		SceneSwitcher::get_instance().registerScene("WIN_SCREEN", winScreen);

		SaveScreen* saveScreen = new SaveScreen(sceneId++);
		SceneSwitcher::get_instance().registerScene("LOADSCREEN", saveScreen);

		SceneSwitcher::get_instance().switchToScene("MAIN_MENU", false);
		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));
	}
	catch (exception e) {
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}

	LoadLevelFacade levelLoader{ engine };
	LoadLevelFacade level2Loader{ engine };
	LoadLevelFacade level3Loader{ engine };
	LevelBuilder levelOneBuilder{ engine, sceneId++ };
	LevelBuilder levelTwoBuilder{ engine, sceneId++ };
	LevelBuilder levelThreeBuilder{ engine, sceneId++ };
	try {
		levelLoader.load("Assets/Levels/Maps/Level1.json", &levelOneBuilder);
		Level* level = levelOneBuilder.getLevel();
		SceneSwitcher::get_instance().registerScene("LEVEL_1", level);

		level2Loader.load("Assets/Levels/Maps/Level2.json", &levelTwoBuilder);
		Level* level2 = levelTwoBuilder.getLevel();
		SceneSwitcher::get_instance().registerScene("LEVEL_2", level2);

		level3Loader.load("Assets/Levels/Maps/Level3.json", &levelThreeBuilder);
		Level* level3 = levelThreeBuilder.getLevel();
		SceneSwitcher::get_instance().registerScene("LEVEL_3", level3);
	}
	catch (exception e) {
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}

	try {
		while (gameRunning)
		{
			EventSingleton::get_instance().dispatchEvent<FpsUpdateEvent>((Event&)FpsUpdateEvent());
			AppTickEvent60 appTick;
			AppTickEvent30 appTick30;

			engine.pollEvents();
			EventSingleton::get_instance().dispatchEvent<AppTickEvent60>(appTick);
			EventSingleton::get_instance().dispatchEvent<AppTickEvent30>(appTick30);

			// TODO get only the non static objects, without looping thru them again and again
			auto scene = engine.getCurrentScene();
			scene->onUpdate();

			this_thread::sleep_for(chrono::milliseconds(10));
			EventSingleton::get_instance().dispatchEvent<FpsUpdateEvent>((Event&)FpsUpdateEvent());
		}
		Savegame::get_instance().saveGameDataToJsonFile();
	}
	catch (int e) {
		cout << ERRORCODES[e] << endl;
		return EXIT_FAILURE;
	}
	catch (exception e) {
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCES;
}
