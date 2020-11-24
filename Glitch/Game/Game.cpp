#include "pch.h"
#include "Game.h"

bool Game::stopRun(Event& event) {
	gameRunning = false;
	return true;
}

Game::Game()
{
}

void Game::switchToScene(string identifier, const bool _useTransitionScreen)
{
	bool useTransitionScreen = _useTransitionScreen;
	if (DEBUG_MAIN) { useTransitionScreen = false; }

	string transition = "";
	if (useTransitionScreen)
	{
		transition = identifier;
		identifier = "GeneralTransition";
	}

	bool handlingLevel = false;
	if (identifier.find("level") != string::npos)
	{
		handlingLevel = true;
	}

	shared_ptr<Scene> newScene = nullptr;

	if (!handlingLevel)
	{
		newScene = Factory::create(identifier, sceneId++);
	}
	else
	{
		// Todo check which level # and build this number
		LoadLevelFacade levelLoader{ engine };
		LevelBuilder levelOneBuilder{ engine, sceneId++ };
		levelLoader.load("Assets/Levels/Maps/Level1.json", &levelOneBuilder);
		newScene = levelOneBuilder.getLevel();
	}

	if (sceneId > 10) sceneId = 1;
	if (newScene == nullptr) throw exception("NewScene is Nullptr so cant set new scene");

	engine.insertScene(newScene.get());
	engine.setCurrentScene(newScene->getSceneID());

	// Detach and delete the old now inactive scene
	if (currentScene != nullptr)
	{
		currentScene->onDetach();
		engine.deRegisterScene(currentScene->getSceneID());
		cout << "CurrenScene is still managed by: " << currentScene.use_count() << endl;
		if (currentScene.use_count() == 1)
		{
			currentScene.reset();
		}
		else
		{
			throw exception("CurrentScene is still used somewhere. Issues with deleting");
		}
		cout << "CurrenScene is still managed by: " << currentScene.use_count() << endl;
		currentScene = nullptr;
	}

	currentScene = newScene;

	if (currentScene && dynamic_cast<GeneralTransition*>(currentScene.get()))
	{
		((GeneralTransition*)currentScene.get())->setNextScene(transition);
	}
	
	if (currentScene && dynamic_cast<GameScene*>(currentScene.get()))
	{
		((GameScene*)currentScene.get())->registerGame(this);
	}

	cout << "Setting current Scene to: " << engine.getCurrentScene()->getSceneID() << endl;

	currentScene->onAttach();
	currentScene->start();

}

void Game::run() {

	try {

		EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));

		switchToScene("MainMenu", false);

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
