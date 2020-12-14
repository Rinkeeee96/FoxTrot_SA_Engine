#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Characters/Enemies/Jumpkin.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(EnemyTests)
	{
		/*
			TODO:
			bool onCollisionBeginEvent(const Event& event);
			void onUpdate() -> AI
		*/
	public:
		TEST_METHOD(Jumpkin_RemoveHealth_Invincible_Should_NotRemoveHealth)
		{
			// Arrange
			EventDispatcher dispatcher;
			Jumpkin entity{ dispatcher };
			int health = 100;
			entity.setTotalHealth(health);
			entity.setCurrentHealth(health);
			entity.setInvincible(true);
			// Act
			entity.removeHealth(10);
			// Assert
			Assert::AreEqual(100, entity.getCurrentHealth());
		}

		TEST_METHOD(Jumpkin_RemoveHealth_Vincible_Should_RemoveHealth)
		{
			// Arrange
			EventDispatcher dispatcher;
			Jumpkin entity{ dispatcher };
			int health = 100;
			entity.setTotalHealth(health);
			entity.setCurrentHealth(health);
			// Act
			entity.removeHealth(10);
			// Assert
			Assert::AreEqual(90, entity.getCurrentHealth());
		}

		TEST_METHOD(Jumpkin_kill_should_set_health_to_zero)
		{
			// Arrange
			EventDispatcher dispatcher;
			Jumpkin entity{ dispatcher };
			int health = 100;
			entity.setTotalHealth(health);
			entity.setCurrentHealth(health);
			// Act
			entity.kill();
			// Assert
			Assert::AreEqual(0, entity.getCurrentHealth());
			Assert::AreEqual(health, entity.getTotalHealth());
		}

		TEST_METHOD(Jumpkin_respawn_should_set_newX_and_newY)
		{
			// Arrange
			EventDispatcher dispatcher;
			Jumpkin entity{ dispatcher };
			float oldX = 100;
			float oldY = 100;
			entity.setPositionX(oldX);
			entity.setPositionY(oldY);

			int spawnX = 10;
			int spawnY = 10;
			entity.setSpawnX(spawnX);
			entity.setSpawnY(spawnY);
			// Act
			entity.respawn();
			// Assert
			Assert::AreNotEqual(oldX, entity.getPositionX());
			Assert::AreNotEqual(oldY, entity.getPositionY());
		}

		TEST_METHOD(Jumpkin_GetIsDead_With_Health_Should_Return_False)
		{
			// Arrange
			EventDispatcher dispatcher;
			Jumpkin entity{ dispatcher };
			int health = 100;
			entity.setTotalHealth(health);
			entity.setCurrentHealth(health);
			// Act
			auto result = entity.getIsDead();
			// Assert
			Assert::IsFalse(result);
		}

		TEST_METHOD(Jumpkin_GetIsDead_Without_Health_Should_Return_True)
		{
			// Arrange
			EventDispatcher dispatcher;
			Jumpkin entity{ dispatcher };
			// Act
			entity.setCurrentHealth(0);
			auto result = entity.getIsDead();
			// Assert
			Assert::IsTrue(result);
		}
	};
}