#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Characters/Enemies/Jumpkin.h>
#include <Game/Commands/Builder/CommandBuilder.h>
#include <Game/Scenes/Statemachine/SceneStateMachine.h>
#include "../../mocks/MockScene.h"
#include "../../mocks/MockPlayer.h"
#include "../../mocks/MockJumpkin.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(EnemyTests)
	{
	public:
		TEST_METHOD(Jumpkin_On_Update_Player_Left_Should_Turn_Left)
		{
			// Arrange
			unique_ptr<Engine> engine = make_unique<Engine>();
			CommandBuilder commandBuilder;
			engine->start();
			engine->useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());

			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			shared_ptr<SceneStateMachine> statemachine = make_shared<SceneStateMachine>(engine, savegame);

			unique_ptr<MockScene> scene = make_unique<MockScene>();

			shared_ptr<Jumpkin> jumpkin = make_shared<MockJumpkin>(1, scene->getEventDispatcher());
			jumpkin->setPositionX(300);
			jumpkin->setPositionY(200);
			jumpkin->setStatic(true);

			auto result = jumpkin->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				jumpkin->registerSprite(it->first, it->second);
				it++;
			}
			jumpkin->changeToState(0);

			float oldX = jumpkin->getPositionX();

			shared_ptr<Player> player = make_shared<MockPlayer>(2, scene->getEventDispatcher());
			player->setPositionX(100);
			player->setPositionY(200);

			result = player->buildSpritemap(1);
			it = result.begin();
			while (it != result.end())
			{
				player->registerSprite(it->first, it->second);
				it++;
			}
			player->changeToState(0);

			jumpkin->setPlayer(player.get());

			scene->addNewObjectToLayer(1, jumpkin, true, false);
			scene->addNewObjectToLayer(1, player, true, false);
			engine->insertScene(move(scene));
			engine->setCurrentScene(1);

			// Act
			engine->update();
			jumpkin->onUpdate(1);
			engine->update();

			// Assert
			Assert::AreEqual("Assets/Sprites/Enemies/Jumpkin/Jumpkin_action_left_1.png", jumpkin->GetCurrentSprite()->getFileName());
		}

		TEST_METHOD(Jumpkin_On_Update_Player_Right_Should_Turn_Right)
		{
			// Arrange
			unique_ptr<Engine> engine = make_unique<Engine>();
			CommandBuilder commandBuilder;
			engine->start();
			engine->useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());

			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			shared_ptr<SceneStateMachine> statemachine = make_shared<SceneStateMachine>(engine, savegame);

			unique_ptr<MockScene> scene = make_unique<MockScene>();

			shared_ptr<Jumpkin> jumpkin = make_shared<MockJumpkin>(1, scene->getEventDispatcher());
			jumpkin->setPositionX(100);
			jumpkin->setPositionY(200);
			jumpkin->setStatic(true);

			auto result = jumpkin->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				jumpkin->registerSprite(it->first, it->second);
				it++;
			}
			jumpkin->changeToState(0);

			float oldX = jumpkin->getPositionX();

			shared_ptr<Player> player = make_shared<MockPlayer>(2, scene->getEventDispatcher());
			player->setPositionX(300);
			player->setPositionY(200);

			result = player->buildSpritemap(1);
			it = result.begin();
			while (it != result.end())
			{
				player->registerSprite(it->first, it->second);
				it++;
			}
			player->changeToState(0);

			jumpkin->setPlayer(player.get());

			scene->addNewObjectToLayer(1, jumpkin, true, false);
			scene->addNewObjectToLayer(1, player, true, false);
			engine->insertScene(move(scene));
			engine->setCurrentScene(1);

			// Act
			engine->update();
			jumpkin->onUpdate(1);
			engine->update();

			// Assert
			Assert::AreEqual("Assets/Sprites/Enemies/Jumpkin/Jumpkin_action_right_1.png", jumpkin->GetCurrentSprite()->getFileName());
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