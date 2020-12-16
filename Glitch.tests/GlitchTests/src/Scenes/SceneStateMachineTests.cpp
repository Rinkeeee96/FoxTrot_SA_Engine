#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Scenes/Statemachine/SceneStateMachine.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	/*
		SceneStateMachine(Engine& engine, shared_ptr<Savegame> savegame);
		~SceneStateMachine();

		void switchToScene(string const identifier, bool useTransitionScreen, bool playSound = true);
		void updateCurrentScene();
		string& getCurrentLevelIdentifier();
	*/

	TEST_CLASS(SceneTests)
	{
	public:
		TEST_METHOD(SceneStateMachineScene_)
		{
			// Arrange
			Engine engine;
			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			SceneStateMachine statemachine{ engine, savegame };
			// Act
			statemachine.switchToScene("MainMenu", false, false);
			// Assert
			Assert::IsTrue(false);
		}
	};
}