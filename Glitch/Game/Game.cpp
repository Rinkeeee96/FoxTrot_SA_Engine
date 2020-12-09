#include "pch.h"
#include "Game.h"
#include "Commands/Builder/CommandBuilder.h"
#include "Game/Commands/CharacterCommands/StopMovementCommand.h"

Game::Game()
{
	commandBuilder = new CommandBuilder();
	savegame = shared_ptr<Savegame>(new Savegame());
}


int Game::run() {

	try {
		engine.useCustomCommandInvoker(commandBuilder->readBindingsAndCreateInvoker());

		if (GameKeypressInvoker* e = dynamic_cast<GameKeypressInvoker*>(engine.getKeypressedInvoker())) {
			commandBuilder->buildGlobalCommands(e);
		}
		stateMachine->switchToScene("MainMenu", false);
		string path = "Assets/SaveGame/saveGameData.json";
		savegame->readSaveGameDataFromJson(path);
		stateMachine->switchToScene("MainMenu", false);

		engine.setEngineRunning(true);

		while (engine.getEngineRunning())
		{
			engine.updateFps();
			engine.onUpdate();
			// TODO get only the non static objects, without looping thru them again and again
			stateMachine->updateCurrentScene();
			this_thread::sleep_for(chrono::milliseconds(10));
			engine.updateFps();
		}
		savegame->saveGameDataToJsonFile();
	}
	catch (int e) {
		cout << ERRORCODES[e] << endl;
		return EXIT_FAILURE;
	}
	catch (exception e) {
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
