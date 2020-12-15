#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Triggers/DeathTrigger.h>
#include <Game/Characters/Enemies/Slime.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(TriggerTests)
	{
	public:
		TEST_METHOD(DeathTrigger_With_Player_Should_Kill_Player)
		{
			// Arrange
			EventDispatcher dispatcher;
			DeathTrigger entity{ 1, dispatcher };
			Player player{ 2, dispatcher };
			player.setTotalHealth(5);
			player.setCurrentHealth(5);
			// Act
			map<int, vector<Direction>> direction;
			direction[player.getObjectId()] = { Direction::DOWN };
			direction[entity.getObjectId()] = { Direction::UP };

			dispatcher.dispatchEvent<OnCollisionBeginEvent>((Event&)OnCollisionBeginEvent(player, entity, direction));
			// Assert
			Assert::IsTrue(player.getIsDead());
		}

		TEST_METHOD(DeathTrigger_With_Slime_Should_Kill_Player)
		{
			// Arrange
			EventDispatcher dispatcher;
			DeathTrigger entity{ 1, dispatcher };
			Slime slime{ 2, dispatcher };
			slime.setTotalHealth(5);
			slime.setCurrentHealth(5);
			// Act
			map<int, vector<Direction>> direction;
			direction[slime.getObjectId()] = { Direction::DOWN };
			direction[entity.getObjectId()] = { Direction::UP };

			dispatcher.dispatchEvent<OnCollisionBeginEvent>((Event&)OnCollisionBeginEvent(slime, entity, direction));
			// Assert
			Assert::IsTrue(slime.getIsDead());
		}
	};
}