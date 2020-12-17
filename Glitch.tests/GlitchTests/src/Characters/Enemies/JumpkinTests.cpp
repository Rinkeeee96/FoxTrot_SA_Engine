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
		TEST_METHOD(Jumpkin_On_Update_Player_Left_Should_Go_Left)
		{
			// Arrange

			// Act

			// Assert
			Assert::IsTrue(false);
		}

		TEST_METHOD(Jumpkin_On_Update_Player_Right_Should_Go_Right)
		{
			// Arrange

			// Act

			// Assert
			Assert::IsTrue(false);
		}

		TEST_METHOD(Jumpkin_On_Update_Player_In_Sight_Should_Move)
		{
			// Arrange

			// Act

			// Assert
			Assert::IsTrue(false);
		}
		TEST_METHOD(Jumpkin_On_Collision_Begin_Top_Should_Remove_Jumpkin)
		{
			// Arrange
			EventDispatcher dispatcher;
			shared_ptr<Jumpkin> entity = make_shared<Jumpkin>(1, dispatcher);
			shared_ptr<Player> player = make_shared<Player>(2, dispatcher);
			auto result = player->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				player->registerSprite(it->first, it->second);
				it++;
			}
			player->setTotalHealth(5);
			player->setCurrentHealth(5);
			entity->setTotalHealth(5);
			entity->setCurrentHealth(5);
			entity->setPlayer(player.get());
			// Act
			map<int, vector<Direction>> direction;
			direction[player->getObjectId()] = { Direction::DOWN };
			direction[entity->getObjectId()] = { Direction::UP };

			dispatcher.dispatchEvent<OnCollisionBeginEvent>((Event&)OnCollisionBeginEvent(player, entity, direction));
			// Assert
			Assert::AreEqual(entity->getCurrentHealth(), 0);
			Assert::IsTrue(entity->getIsDead());
			Assert::AreEqual(player->getCurrentHealth(), 5);
			Assert::IsFalse(player->getIsDead());
		}

		TEST_METHOD(Jumpkin_On_Collision_Begin_Bottom_Should_Damage_Player)
		{
			// Arrange
			EventDispatcher dispatcher;
			shared_ptr<Jumpkin> entity = make_shared<Jumpkin>(1, dispatcher);
			shared_ptr<Player> player = make_shared<Player>(2, dispatcher);
			auto result = player->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				player->registerSprite(it->first, it->second);
				it++;
			}
			player->setTotalHealth(5);
			player->setCurrentHealth(5);
			entity->setTotalHealth(5);
			entity->setCurrentHealth(5);
			entity->setPlayer(player.get());
			// Act
			map<int, vector<Direction>> direction;
			direction[player->getObjectId()] = { Direction::UP };
			direction[entity->getObjectId()] = { Direction::DOWN };

			dispatcher.dispatchEvent<OnCollisionBeginEvent>((Event&)OnCollisionBeginEvent(player, entity, direction));
			// Assert
			Assert::AreNotEqual(player->getCurrentHealth(), 5);
			Assert::AreEqual(entity->getCurrentHealth(), 5);
			Assert::IsFalse(entity->getIsRemoved());
		}
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