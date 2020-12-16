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
		TEST_METHOD(Level_Win_Should_Stop_Level)
		{
			// Arrange
			Engine engine;
			CommandBuilder commandBuilder;
			engine.start();
			engine.useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());
			EventDispatcher dispatcher;

			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			SceneStateMachine statemachine{ engine, savegame };
			Level level{ 1, 100, 100, engine, statemachine };
			Player player{ dispatcher };
			level.addNewObjectToLayer(1, &player, true, true);
			level.setPlayer(&player);
			level.registerSavegame(savegame);
			level.start(false);
			level.createLayer(1, true, true);
			// Act
			level.setWin(true);
			level.onUpdate();
			// Assert
			Assert::IsTrue(level.getWin());
		}

		TEST_METHOD(Level_Death_Should_Stop_Level)
		{
			// Arrange
			Engine engine;
			CommandBuilder commandBuilder;
			engine.start();
			engine.useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());
			EventDispatcher dispatcher;

			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			SceneStateMachine statemachine{ engine, savegame };
			Level level{ 1, 100, 100, engine, statemachine };
			Player player{ dispatcher };
			level.addNewObjectToLayer(1, &player, true, true);
			level.setPlayer(&player);
			level.registerSavegame(savegame);
			level.start(false);
			level.createLayer(1, true, true);
			// Act
			player.kill();
			level.onUpdate();
			// Assert
			Assert::IsFalse(level.getWin());
		}
	};
}