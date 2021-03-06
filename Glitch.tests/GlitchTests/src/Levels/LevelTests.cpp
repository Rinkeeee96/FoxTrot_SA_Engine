#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Levels/Level.h>
#include <Game/Scenes/Statemachine/SceneStateMachine.h>
#include <Game/Commands/Builder/CommandBuilder.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(LevelTests)
	{
	public:
		TEST_METHOD(Level_Death_Should_Stop_Level)
		{
			// Arrange
			unique_ptr<Engine> engine = make_unique<Engine>();
			CommandBuilder commandBuilder;
			engine->start();
			engine->useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());
			EventDispatcher dispatcher;

			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			shared_ptr<SceneStateMachine> statemachine = make_shared<SceneStateMachine>(engine, savegame);
			unique_ptr<Level> level = make_unique<Level>( 1, 100, 100, engine, statemachine );
			Level* levelptr = level.get();
			engine->insertScene(std::move(level));
			engine->setCurrentScene(1);
			shared_ptr<Player> player = make_shared<Player>(dispatcher);
			levelptr->addNewObjectToLayer(1, player, true, true);
			levelptr->setPlayer(player);
			levelptr->registerSavegame(savegame);
			levelptr->start(false);
			levelptr->createLayer(1, true, true);
			// Act
			player->kill();
			levelptr->onUpdate(1);
			// Assert
			Assert::IsFalse(levelptr->getWin());
		}
	};
}