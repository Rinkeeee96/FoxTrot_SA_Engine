#include "pch.h"
#include "Game.h"
Game::Game()
{
	stateMachine = shared_ptr<SceneStateMachine>(new SceneStateMachine(engine));
}

int Game::run() {

	try {
		stateMachine->switchToScene("MainMenu", false);

		engine.setEngineRunning(true);

		while (engine.getEngineRunning())
		{
			engine.updateFps();

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
