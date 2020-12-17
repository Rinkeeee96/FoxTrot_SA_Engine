#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Characters/Player/Player.h>
#include <Game/States/Player/GodState.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(StatesTests)
	{
	public:
		TEST_METHOD(GodState_Should_Set_Invincible)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ 2, dispatcher };
			player.setCanJump(false);
			player.setTotalHealth(5);
			player.setCurrentHealth(3);
			player.getStateMachine().changeState(new GodState, &player);
			// Act
			player.onUpdate(1);
			// Assert
			Assert::IsTrue(player.getInvincible());
		}

		TEST_METHOD(GodState_Should_Set_CanJump)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ 2, dispatcher };
			player.setCanJump(false);
			player.setTotalHealth(5);
			player.setCurrentHealth(3);
			player.getStateMachine().changeState(new GodState, &player);
			// Act
			player.onUpdate(1);
			// Assert
			Assert::IsTrue(player.getCanJump());
		}

		TEST_METHOD(GodState_Should_Set_HealthMax)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ 2, dispatcher };
			player.setCanJump(false);
			player.setTotalHealth(5);
			player.setCurrentHealth(3);
			player.getStateMachine().changeState(new GodState, &player);
			// Act
			player.onUpdate(1);
			// Assert
			Assert::AreEqual(player.getCurrentHealth(), 5);
		}
	};
}