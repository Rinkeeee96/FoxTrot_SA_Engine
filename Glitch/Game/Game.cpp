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

	LoadLevelFacade levelLoader{ engine };
	LevelBuilder levelOneBuilder{ engine, sceneId++ };

	MainMenu* mainMenu = new MainMenu(sceneId++);
	SceneSwitcher::get_instance().registerScene("MAIN_MENU", mainMenu);

	GeneralTransition* generalTransitionScene = new GeneralTransition(160);
	SceneSwitcher::get_instance().registerScene("GENERAL_TRANSITION_SCENE", generalTransitionScene);

	try {
		levelLoader.load("Assets/Levels/Maps/Level1.json", &levelOneBuilder);
		auto level = levelOneBuilder.getLevel();
		SceneSwitcher::get_instance().registerScene("LEVEL_1", level);
	}
	catch (exception e) {
		// TODO show message
		return;
	}
	

	SceneSwitcher::get_instance().switchToScene("MAIN_MENU");
	EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));

	engine.startTickThreads();
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
	engine.stopTickThreads();
}