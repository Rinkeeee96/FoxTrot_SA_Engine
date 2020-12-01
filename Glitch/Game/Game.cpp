#include "pch.h"
#include "Game.h"

bool Game::stopRun(Event& event) {
	gameRunning = false;
	return true;
}

bool Game::onKeyPressed(Event& event)
{
	auto keyPressedEvent = static_cast<KeyPressedEvent&>(event);
	// TODO command pattern
	switch (keyPressedEvent.GetKeyCode())
	{
	case KeyCode::KEY_ESCAPE:
		stateMachine->switchToScene("PauseScreen", false);
		break;
	default:
		return false;
	}
	return true;
}

Game::Game()
{
	stateMachine = shared_ptr<SceneStateMachine>(new SceneStateMachine(engine));
	EventSingleton::get_instance().setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(Game::onKeyPressed));
}

int Game::run() {

	try {
		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));
		stateMachine->switchToScene("PauseScreen", false);

		while (gameRunning)
		{
			EventSingleton::get_instance().dispatchEvent<FpsUpdateEvent>((Event&)FpsUpdateEvent());
			AppTickEvent60 appTick;
			AppTickEvent30 appTick30;

			engine.pollEvents();
			EventSingleton::get_instance().dispatchEvent<AppTickEvent60>(appTick);
			EventSingleton::get_instance().dispatchEvent<AppTickEvent30>(appTick30);

			// TODO get only the non static objects, without looping thru them again and again
			stateMachine->updateCurrentScene();

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
