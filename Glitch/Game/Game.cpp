#include "pch.h"
#include "Game.h"

bool Game::stopRun(Event& event) {
	gameRunning = false;
	return true;
}

Game::Game()
{
	stateMachine = shared_ptr<SceneStateMachine>(new SceneStateMachine(engine));
}

int Game::run() {

	try {
		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));
		stateMachine->switchToScene("MainMenu", false);

		while (gameRunning)
		{
			engine.updateFps();
			AppTickEvent60 appTick;
			AppTickEvent30 appTick30;

			engine.pollEvents();
			engine.onUpdate();

			// TODO get only the non static objects, without looping thru them again and again
			stateMachine->updateCurrentScene();

			this_thread::sleep_for(chrono::milliseconds(10));
			engine.updateFps();
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
