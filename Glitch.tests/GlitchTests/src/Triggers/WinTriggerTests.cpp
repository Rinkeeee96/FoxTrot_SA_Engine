#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Triggers/WinTrigger.h>
#include <Game/Commands/Builder/CommandBuilder.h>
#include <Game/Scenes/Statemachine/SceneStateMachine.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(TriggerTests)
	{
	public:
		TEST_METHOD(WinTrigger_Player_Collision_Begin_Should_Set_Level_Win)
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

			WinTrigger winTrigger{ 1, level, dispatcher };

			Player player{ 2, dispatcher };
			player.setTotalHealth(5);
			player.setCurrentHealth(5);
			// Act
			map<int, vector<Direction>> direction;
			direction[player.getObjectId()] = { Direction::DOWN };
			direction[winTrigger.getObjectId()] = { Direction::UP };

			dispatcher.dispatchEvent<OnCollisionBeginEvent>((Event&)OnCollisionBeginEvent(player, winTrigger, direction));
			// Assert
			Assert::IsTrue(level.getWin());
		}
	};
}