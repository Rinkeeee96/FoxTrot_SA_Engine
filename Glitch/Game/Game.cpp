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

void Game::run() {
	// TODO throw error when something goes wrong in sceneSwitcher
	try {
		MainMenu* mainMenu = new MainMenu(sceneId++);
		SceneSwitcher::get_instance().registerScene("MAIN_MENU", mainMenu);

		GeneralTransition* generalTransitionScene = new GeneralTransition(160);
		SceneSwitcher::get_instance().registerScene("GENERAL_TRANSITION_SCENE", generalTransitionScene);

		SceneSwitcher::get_instance().switchToScene("MAIN_MENU", false);
		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));

		Overworld* overWorld = new Overworld(7);
		SceneSwitcher::get_instance().registerScene("OVERWORLD", overWorld);
	}
	catch (exception e) {
		// TODO show message
		return;
	}

	LoadLevelFacade levelLoader{ engine };
	LevelBuilder levelOneBuilder{ engine, sceneId++ };
	try {
		levelLoader.load("Assets/Levels/Maps/Level1.json", &levelOneBuilder);
		auto level = levelOneBuilder.getLevel();
		SceneSwitcher::get_instance().registerScene("LEVEL_1", level);
	}
	catch (exception e) {
		// TODO show message
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
			auto scene = engine.getCurrentScene();
			scene->onUpdate();

			this_thread::sleep_for(chrono::milliseconds(10));
		}
	}
	catch (int e) {
		// TODO show message
	}
	catch (exception e) {
		// TODO show message
	}
}