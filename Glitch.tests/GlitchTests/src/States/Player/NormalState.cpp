#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Characters/Player/Player.h>
#include <Game/States/Player/NormalState.h>
#include <Game/States/Player/DamageCooldownState.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(StatesTests)
	{
	public:
		TEST_METHOD(NormalState_PlayerDefault_Should_Be_NormalState)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ 2, dispatcher };
			player.setCanJump(false);
			player.setTotalHealth(5);
			player.setCurrentHealth(3);
			// Act
			player.onUpdate(1);
			IState<Player>& result = player.getStateMachine().getCurrentState();
			// Assert
			if (typeid(NormalState) == typeid(result)) {
				Assert::IsTrue(true);
			}
			else {
				Assert::IsTrue(false);
			}
		}

		TEST_METHOD(NormalState_Should_Set_Vincible)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ 2, dispatcher };
			player.setCanJump(false);
			player.setTotalHealth(5);
			player.setInvincible(true);
			// Act
			player.getStateMachine().changeState(new NormalState, &player);
			player.onUpdate(1);
			// Assert
			Assert::IsFalse(player.getInvincible());
		}

		TEST_METHOD(NormalState_HitTaken_Should_Set_DamageCooldownState)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ 2, dispatcher };
			player.setCanJump(false);
			player.setTotalHealth(5);
			player.setCurrentHealth(3);
			// Act
			player.onUpdate(1);
			player.setCurrentHealth(2);
			player.onUpdate(1);
			IState<Player>& result = player.getStateMachine().getCurrentState();
			// Assert
			if (typeid(DamageCooldownState) == typeid(result)) {
				Assert::IsTrue(true);
			}
			else {
				Assert::IsTrue(false);
			}
		}
	};
}