#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Characters/Enemies/Fleye.h>
#include <Game/Commands/Builder/CommandBuilder.h>
#include <Game/Scenes/Statemachine/SceneStateMachine.h>
#include "../../mocks/MockScene.h"
#include "../../mocks/MockPlayer.h"
#include "../../mocks/MockFleye.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	/*
		TODO:
		bool onCollisionBeginEvent(const Event& event);
		void onUpdate() -> AI
	*/
	TEST_CLASS(EnemyTests)
	{
	public:
		TEST_METHOD(Fleye_On_Update_Player_Beneath_Should_Go_Down)
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

			shared_ptr<Fleye> fleye = make_shared<MockFleye>(1, scene->getEventDispatcher());
			fleye->setPositionX(100);
			fleye->setPositionY(600);
			fleye->setStatic(true);

			auto result = fleye->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				fleye->registerSprite(it->first, it->second);
				it++;
			}
			fleye->changeToState(0);

			float oldY = fleye->getPositionY();

			shared_ptr <Player> player = make_shared<MockPlayer>(2, scene->getEventDispatcher());
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

			fleye->setPlayer(player.get());

			scene->addNewObjectToLayer(1, fleye, true, false);
			scene->addNewObjectToLayer(1, player, true, false);
			engine->insertScene(move(scene));
			engine->setCurrentScene(1);

			// Act
			engine->update();
			fleye->onUpdate(1);
			engine->update();

			// Assert
			Assert::AreNotEqual(oldY, fleye->getPositionY());
		}

		TEST_METHOD(Fleye_On_Update_Player_Not_Beneath_Should_Stay_Same)
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

			shared_ptr<Fleye> fleye = make_shared<MockFleye>(1, scene->getEventDispatcher());
			fleye->setPositionX(100);
			fleye->setPositionY(600);
			fleye->setStatic(true);

			auto result = fleye->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				fleye->registerSprite(it->first, it->second);
				it++;
			}
			fleye->changeToState(0);

			float oldY = fleye->getPositionY();

			shared_ptr <Player> player = make_shared<MockPlayer>(2, scene->getEventDispatcher());
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

			fleye->setPlayer(player.get());

			scene->addNewObjectToLayer(1, fleye, true, false);
			scene->addNewObjectToLayer(1, player, true, false);
			engine->insertScene(move(scene));
			engine->setCurrentScene(1);

			// Act
			engine->update();
			fleye->onUpdate(1);
			engine->update();

			// Assert
			Assert::AreEqual(oldY, fleye->getPositionY());
		}

		TEST_METHOD(Fleye_On_Update_Player_Left_Should_Go_Left)
		{
			// Arrange

			// Act

			// Assert
			Assert::IsTrue(false);
		}

		TEST_METHOD(Fleye_On_Update_Player_Right_Should_Go_Right)
		{
			// Arrange

			// Act

			// Assert
			Assert::IsTrue(false);
		}

		TEST_METHOD(Fleye_On_Update_Player_In_Sight_Should_Move)
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

			shared_ptr<Fleye> fleye = make_shared<MockFleye>(1, scene->getEventDispatcher());
			fleye->setPositionX(300);
			fleye->setPositionY(600);
			fleye->setStatic(true);

			auto result = fleye->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				fleye->registerSprite(it->first, it->second);
				it++;
			}
			fleye->changeToState(0);

			float oldX = fleye->getPositionX();

			shared_ptr <Player> player = make_shared<MockPlayer>(2, scene->getEventDispatcher());
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

			fleye->setPlayer(player.get());

			scene->addNewObjectToLayer(1, fleye, true, false);
			scene->addNewObjectToLayer(1, player, true, false);
			engine->insertScene(move(scene));
			engine->setCurrentScene(1);

			// Act
			engine->update();
			fleye->onUpdate(1);
			engine->update();

			// Assert
			Assert::IsTrue(fleye->getPositionX() < oldX);
		}

		TEST_METHOD(Fleye_On_Collision_Begin_Top_Should_Remove_Fleye)
		{
			// Arrange
			EventDispatcher dispatcher;
			shared_ptr<Fleye> entity = make_shared<Fleye>(1, dispatcher);
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

		TEST_METHOD(Fleye_On_Collision_Begin_Bottom_Should_Damage_Player)
		{
			// Arrange
			EventDispatcher dispatcher;
			shared_ptr<Fleye> entity = make_shared<Fleye>(1, dispatcher);
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


		TEST_METHOD(Fleye_RemoveHealth_Invincible_Should_NotRemoveHealth)
		{
			// Arrange
			EventDispatcher dispatcher;
			Fleye entity{ dispatcher };
			int health = 100;
			entity.setTotalHealth(health);
			entity.setCurrentHealth(health);
			entity.setInvincible(true);
			// Act
			entity.removeHealth(10);
			// Assert
			Assert::AreEqual(100, entity.getCurrentHealth());
		}

		TEST_METHOD(Fleye_RemoveHealth_Vincible_Should_RemoveHealth)
		{
			// Arrange
			EventDispatcher dispatcher;
			Fleye entity{ dispatcher };
			int health = 100;
			entity.setTotalHealth(health);
			entity.setCurrentHealth(health);
			// Act
			entity.removeHealth(10);
			// Assert
			Assert::AreEqual(90, entity.getCurrentHealth());
		}

		TEST_METHOD(Fleye_kill_should_set_health_to_zero)
		{
			// Arrange
			EventDispatcher dispatcher;
			Fleye entity{ dispatcher };
			int health = 100;
			entity.setTotalHealth(health);
			entity.setCurrentHealth(health);
			// Act
			entity.kill();
			// Assert
			Assert::AreEqual(0, entity.getCurrentHealth());
			Assert::AreEqual(health, entity.getTotalHealth());
		}

		TEST_METHOD(Fleye_respawn_should_set_newX_and_newY)
		{
			// Arrange
			EventDispatcher dispatcher;
			Fleye entity{ dispatcher };
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

		TEST_METHOD(Fleye_GetIsDead_With_Health_Should_Return_False)
		{
			// Arrange
			EventDispatcher dispatcher;
			Fleye entity{ dispatcher };
			int health = 100;
			entity.setTotalHealth(health);
			entity.setCurrentHealth(health);
			// Act
			auto result = entity.getIsDead();
			// Assert
			Assert::IsFalse(result);
		}

		TEST_METHOD(Fleye_GetIsDead_Without_Health_Should_Return_True)
		{
			// Arrange
			EventDispatcher dispatcher;
			Fleye entity{ dispatcher };
			// Act
			entity.setCurrentHealth(0);
			auto result = entity.getIsDead();
			// Assert
			Assert::IsTrue(result);
		}
	};
}