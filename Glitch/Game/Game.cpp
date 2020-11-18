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

	string file = "Assets/Savegame/saveGameData.json";
	//Savegame::get_instance().readSaveGameDataFromJson(file);

	LoadLevelFacade levelLoader{ engine };
	LevelBuilder levelOneBuilder{ engine, sceneId++ };

	MainMenu* mainMenu = new MainMenu(sceneId++);
	SceneSwitcher::get_instance().registerScene("MAIN_MENU", mainMenu);

	SaveScreen* saveScreen = new SaveScreen(sceneId++);
	SceneSwitcher::get_instance().registerScene("SAVE_SCREEN", saveScreen);

	GeneralTransition* generalTransitionScene = new GeneralTransition(160);
	SceneSwitcher::get_instance().registerScene("GENERAL_TRANSITION_SCENE", generalTransitionScene);

	levelLoader.load("Assets/Levels/Maps/Level1.json", &levelOneBuilder);
	auto level = levelOneBuilder.getLevel();
	SceneSwitcher::get_instance().registerScene("LEVEL_1", level);

	SceneSwitcher::get_instance().switchToScene("MAIN_MENU");
	EventSingleton::get_instance().setEventCallback<WindowCloseEvent>(BIND_EVENT_FN(Game::stopRun));

	SaveGameData data;
	data.achievements.push_back("Take inventory");
	data.saveGameName = "name";
	data.totalScore = 100;
	Item item;
	item.itemCount = 10;
	item.itemName = "Sword";
	data.characterData.inventory.items.push_back(item);
	data.characterData.inventory.items.push_back(item);

	Savegame::get_instance().saveGameData(1,data);

	Savegame::get_instance().saveGameDataToJsonFile();

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

	Savegame::get_instance().saveGameDataToJsonFile();

	engine.stopTickThreads();
}