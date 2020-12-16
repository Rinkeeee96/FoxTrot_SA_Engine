#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Levels/LoadLevelFacade.h>
#include <Game/Scenes/Statemachine/SceneStateMachine.h>
#include <Game/Commands/Builder/CommandBuilder.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(LevelTests)
	{
	public:
		TEST_METHOD(LoadFacade_Load_Non_ExistingFile_Should_ThrowError)
		{
			// Arrange
			Engine engine;
			EventDispatcher dispatcher;
			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			SceneStateMachine statemachine{ engine, savegame };
			LoadLevelFacade levelLoader{ engine };
			LevelBuilder levelOneBuilder{ engine, 1, statemachine };

			// Act
			try {
				levelLoader.load("TestAssetsGame/nonExisting.json", &levelOneBuilder);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "file not found exception");
			}
		}

		TEST_METHOD(LoadFacade_Load_InvalidFile_Existing_Should_ThrowError)
		{
			// Arrange
			Engine engine;
			LoadLevelFacade levelLoader{ engine };
			EventDispatcher dispatcher;
			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			SceneStateMachine statemachine{ engine, savegame };
			LevelBuilder levelOneBuilder{ engine, 1, statemachine };

			// Act
			try {
				levelLoader.load("TestAssetsGame/invalidLevel.json", &levelOneBuilder);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "Something went wrong validating file, make sure the file is correct");
			}
		}

		TEST_METHOD(LoadFacade_Load_ValidFile_Existing_Should_Create_lEVEL)
		{
			// Arrange
			Engine engine;
			CommandBuilder commandBuilder;
			engine.start();
			engine.useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());
			EventDispatcher dispatcher;
			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			SceneStateMachine statemachine{ engine, savegame };
			LevelBuilder levelOneBuilder{ engine, 1, statemachine };
			LoadLevelFacade levelLoader{ engine };
			// Act
			levelLoader.load("TestAssetsGame/validLevel.json", &levelOneBuilder);
			// Assert
			Assert::IsTrue(true);
		}
	};
}