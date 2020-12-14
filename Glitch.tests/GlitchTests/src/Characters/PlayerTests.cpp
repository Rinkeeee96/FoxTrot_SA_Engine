#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Characters/Player/Player.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(PlayerTests)
	{
	public:
		/*
			TODO:
			bool onCollisionBeginEvent(const Event& event);
			bool onCollisionEndEvent(const Event& event);
		*/
		TEST_METHOD(Player_RemoveHealth_Invincible_Should_NotRemoveHealth)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ dispatcher };
			int health = 100;
			player.setTotalHealth(health);
			player.setCurrentHealth(health);
			player.setInvincible(true);
			// Act
			player.removeHealth(10);
			// Assert
			Assert::AreEqual(100, player.getCurrentHealth());
		}

		TEST_METHOD(Player_RemoveHealth_Vincible_Should_RemoveHealth)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ dispatcher };
			int health = 100;
			player.setTotalHealth(health);
			player.setCurrentHealth(health);
			// Act
			player.removeHealth(10);
			// Assert
			Assert::AreEqual(90, player.getCurrentHealth());
		}

		TEST_METHOD(Player_kill_should_set_health_to_zero)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ dispatcher };
			int health = 100;
			player.setTotalHealth(health);
			player.setCurrentHealth(health);
			// Act
			player.kill();
			// Assert
			Assert::AreEqual(0, player.getCurrentHealth());
			Assert::AreEqual(health, player.getTotalHealth());
		}

		TEST_METHOD(Player_respawn_should_set_newX_and_newY)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ dispatcher };
			float oldX = 100;
			float oldY = 100;
			player.setPositionX(oldX);
			player.setPositionY(oldY);

			int spawnX = 10;
			int spawnY = 10;
			player.setSpawnX(spawnX);
			player.setSpawnY(spawnY);
			// Act
			player.respawn();
			// Assert
			Assert::AreNotEqual(oldX, player.getPositionX());
			Assert::AreNotEqual(oldY, player.getPositionY());
		}

		TEST_METHOD(Player_GetIsDead_With_Health_Should_Return_False)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ dispatcher };
			int health = 100;
			player.setTotalHealth(health);
			player.setCurrentHealth(health);
			// Act
			auto result = player.getIsDead();
			// Assert
			Assert::IsFalse(result);
		}

		TEST_METHOD(Player_GetIsDead_Without_Health_Should_Return_True)
		{
			// Arrange
			EventDispatcher dispatcher;
			Player player{ dispatcher };
			// Act
			player.setCurrentHealth(0);
			auto result = player.getIsDead();
			// Assert
			Assert::IsTrue(result);
		}
	};
}