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


		// Register the buttons, shortcut, should be places elsewhere
		auto defaultBtnSprite = new SpriteObject(101013, 11, 15, 1, 300, "Assets/Buttons/village_orange.png");
		auto hoverBtnSprite = new SpriteObject(101012, 11, 15, 1, 300, "Assets/Buttons/village_gray.png");
		auto transSprite = new SpriteObject(101014, 10, 10, 1, 300, "Assets/transparant.png");
		auto hoverPrimaryBtn = new SpriteObject(101020, 40, 116, 1, 300, "Assets/Buttons/btn_brown_round.png");
		auto buttongreen = new SpriteObject(101010, 40, 116, 1, 300, "Assets/Buttons/btn_green_round.png");
		auto buttonRed = new SpriteObject(101011, 40, 116, 1, 300, "Assets/Buttons/btn_red_round.png");
		engine.loadSprite(*buttonRed);
		engine.loadSprite(*buttongreen);

		engine.loadSprite(*defaultBtnSprite);
		engine.loadSprite(*hoverBtnSprite);
		engine.loadSprite(*transSprite);
		engine.loadSprite(*hoverPrimaryBtn);

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
