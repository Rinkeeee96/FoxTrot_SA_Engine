#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Characters/Player/Player.h>
#include <Game/States/Player/NormalState.h>
#include <Game/States/Player/DamageCooldownState.h>
#include <thread> 
#include <chrono>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(StatesTests)
	{
	public:
		TEST_METHOD(DamageCooldownState_Should_Set_InVincible)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ 2, dispatcher };
			player.setCanJump(false);
			player.setTotalHealth(5);
			player.setInvincible(false);
			// Act
			player.getStateMachine().changeState(new DamageCooldownState, &player);
			player.onUpdate(1);
			// Assert
			Assert::IsTrue(player.getInvincible());
		}

		TEST_METHOD(DamageCooldownState_More_Than_One_Second_Should_Change_To_NormalState)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ 2, dispatcher };
			player.setCanJump(false);
			player.setTotalHealth(5);
			player.setInvincible(true);
			// Act
			player.getStateMachine().changeState(new DamageCooldownState, &player);
			player.onUpdate(1);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			player.onUpdate(1);
			// Assert
			IState<Player>& result = player.getStateMachine().getCurrentState();
			// Assert
			if (typeid(NormalState) == typeid(result)) {
				Assert::IsTrue(true);
			}
			else {
				Assert::IsTrue(false);
			}
		}

		TEST_METHOD(DamageCooldownState_Less_Than_One_Second_Should_Keep_DamageCooldownState)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ 2, dispatcher };
			player.setCanJump(false);
			player.setTotalHealth(5);
			player.setInvincible(true);
			chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
			// Act

			player.getStateMachine().changeState(new DamageCooldownState, &player);
			player.onUpdate(1);

			chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
			std::chrono::milliseconds miliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
			std::chrono::milliseconds ml{ 900 };
			std::this_thread::sleep_for(std::chrono::milliseconds(ml - miliSeconds));
			player.onUpdate(1);
			// Assert
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