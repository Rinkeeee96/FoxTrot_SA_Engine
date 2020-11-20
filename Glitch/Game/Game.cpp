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
	try {
		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));

		MainMenu* mainMenu = new MainMenu(sceneId++);
		SceneSwitcher::get_instance().registerScene("MAIN_MENU", mainMenu);

		GeneralTransition* generalTransitionScene = new GeneralTransition(160);
		SceneSwitcher::get_instance().registerScene("GENERAL_TRANSITION_SCENE", generalTransitionScene);
		
		Overworld* overWorld = new Overworld(sceneId++, engine);
		SceneSwitcher::get_instance().registerScene("OVERWORLD", overWorld);

		DeadScreen* deadScreen = new DeadScreen(sceneId++);
		SceneSwitcher::get_instance().registerScene("DEAD_SCREEN", deadScreen);

		WinScreen* winScreen = new WinScreen(sceneId++);
		SceneSwitcher::get_instance().registerScene("WIN_SCREEN", winScreen);


		SceneSwitcher::get_instance().switchToScene("MAIN_MENU", false);
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

			auto scene = engine.getCurrentScene();
			scene->onUpdate();

			this_thread::sleep_for(chrono::milliseconds(10));
		}
	}
	catch (int e) {
		cout << ERRORCODES[e] << endl;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}