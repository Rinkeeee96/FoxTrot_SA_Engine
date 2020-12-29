#include "pch.h"
#include "Game.h"
#include "Commands/Builder/CommandBuilder.h"
#include "Game/Commands/CharacterCommands/StopMovementCommand.h"

Game::Game()
{
	engine = make_unique<Engine>();
	commandBuilder = shared_ptr<ICommandBuilder>(new CommandBuilder());
	savegame = shared_ptr<Savegame>(new Savegame());
	stateMachine = make_unique<SceneStateMachine>(engine, savegame);
	adHandler = unique_ptr<AdvertisementHandler>(new AdvertisementHandler{engine});
}

/// @brief This function contains the game loop
/// @return 
int Game::run() {
	try {
		engine->start();
		adHandler->getLatestAdvertisements();
		engine->useCustomCommandInvoker(commandBuilder->readBindingsAndCreateInvoker());

		string path = "Assets/SaveGame/saveGameData.json";
		savegame->readSaveGameDataFromJson(path);
		stateMachine->switchToScene("MainMenu", false);

		engine->setEngineRunning(true);

		while (engine->getEngineRunning())
		{
			engine->update();
			engine->updateCurrentScene();
		}
		
		if(EXPORT_GAME_DATA) 
			savegame->saveGameDataToJsonFile();
	}
	catch (exception e) {
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
