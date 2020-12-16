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
		TEST_METHOD(LevelBuilder_Create_Level_Should_Have_Correct_Level)
		{
			// Arrange
			Engine engine;
			CommandBuilder commandBuilder;
			engine.start();
			engine.useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());
			LoadLevelFacade levelLoader{ };
			EventDispatcher dispatcher;
			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			SceneStateMachine statemachine{ engine, savegame };
			LevelBuilder levelOneBuilder{ engine, 1, statemachine };
			// Act
			levelLoader.load("TestAssetsGame/validLevel.json", &levelOneBuilder);
			auto level = levelOneBuilder.getLevel();
			// Assert
			Assert::AreEqual((int)level.get()->getAllDrawablesInScene().size(), 832);
			Assert::AreEqual((int)level.get()->getAllObjectsInScene().size(), 835);
			Assert::AreEqual((int)level.get()->getAllObjectsInSceneRenderPhysics().size(), 817);
		}
	};
}