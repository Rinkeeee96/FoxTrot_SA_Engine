#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Characters/Enemies/SlimeBoss.h>
#include <Game/Commands/Builder/CommandBuilder.h>
#include <Game/Scenes/Statemachine/SceneStateMachine.h>
#include "../../mocks/MockScene.h"
#include "../../mocks/MockPlayer.h"
#include "../../mocks/MockSlimeBoss.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(EnemyTests)
	{
	public:
		TEST_METHOD(SlimeBoss_RemoveHealth_Invincible_Should_NotRemoveHealth)
		{
			// Arrange
			unique_ptr<Engine> engine = make_unique<Engine>();
			CommandBuilder commandBuilder;
			engine->start();
			engine->useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());
			EventDispatcher dispatcher;

			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			shared_ptr<SceneStateMachine> statemachine = make_shared<SceneStateMachine>(engine, savegame);
			unique_ptr<Level> scene = make_unique<Level>(1, 100, 100, engine, statemachine);

			shared_ptr<SlimeBoss> entity = make_shared<MockSlimeBoss>(*scene.get(), 1, scene->getEventDispatcher());
			entity->setPositionX(300);
			entity->setPositionY(200);
			entity->setStatic(true);
			entity->setTotalHealth(5);
			entity->setCurrentHealth(5);

			auto result = entity->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				entity->registerSprite(it->first, it->second);
				it++;
			}
			entity->changeToState(0);
			int health = 100;
			entity->setTotalHealth(health);
			entity->setCurrentHealth(health);
			entity->setInvincible(true);
			// Act
			entity->removeHealth(10);
			// Assert
			Assert::AreEqual(100, entity->getCurrentHealth());
		}

		TEST_METHOD(SlimeBoss_RemoveHealth_Vincible_Should_RemoveHealth)
		{
			// Arrange
			unique_ptr<Engine> engine = make_unique<Engine>();
			CommandBuilder commandBuilder;
			engine->start();
			engine->useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());
			EventDispatcher dispatcher;

			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			shared_ptr<SceneStateMachine> statemachine = make_shared<SceneStateMachine>(engine, savegame);
			unique_ptr<Level> scene = make_unique<Level>(1, 100, 100, engine, statemachine);

			shared_ptr<SlimeBoss> entity = make_shared<MockSlimeBoss>(*scene.get(), 1, scene->getEventDispatcher());
			entity->setPositionX(300);
			entity->setPositionY(200);
			entity->setStatic(true);
			entity->setTotalHealth(5);
			entity->setCurrentHealth(5);

			auto result = entity->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				entity->registerSprite(it->first, it->second);
				it++;
			}
			entity->changeToState(0);
			int health = 100;
			entity->setTotalHealth(health);
			entity->setCurrentHealth(health);
			// Act
			entity->removeHealth(10);
			// Assert
			Assert::AreEqual(90, entity->getCurrentHealth());
		}

		TEST_METHOD(SlimeBoss_kill_should_set_health_to_zero)
		{
			// Arrange
			unique_ptr<Engine> engine = make_unique<Engine>();
			CommandBuilder commandBuilder;
			engine->start();
			engine->useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());
			EventDispatcher dispatcher;

			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			shared_ptr<SceneStateMachine> statemachine = make_shared<SceneStateMachine>(engine, savegame);
			unique_ptr<Level> scene = make_unique<Level>(1, 100, 100, engine, statemachine);

			shared_ptr<SlimeBoss> entity = make_shared<MockSlimeBoss>(*scene.get(), 1, scene->getEventDispatcher());
			entity->setPositionX(300);
			entity->setPositionY(200);
			entity->setStatic(true);
			entity->setTotalHealth(5);
			entity->setCurrentHealth(5);

			auto result = entity->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				entity->registerSprite(it->first, it->second);
				it++;
			}
			entity->changeToState(0);
			int health = 100;
			entity->setTotalHealth(health);
			entity->setCurrentHealth(health);
			// Act
			entity->kill();
			// Assert
			Assert::AreEqual(0, entity->getCurrentHealth());
			Assert::AreEqual(health, entity->getTotalHealth());
		}

		TEST_METHOD(SlimeBoss_GetIsDead_With_Health_Should_Return_False)
		{
			// Arrange
			unique_ptr<Engine> engine = make_unique<Engine>();
			CommandBuilder commandBuilder;
			engine->start();
			engine->useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());
			EventDispatcher dispatcher;

			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			shared_ptr<SceneStateMachine> statemachine = make_shared<SceneStateMachine>(engine, savegame);
			unique_ptr<Level> scene = make_unique<Level>(1, 100, 100, engine, statemachine);

			shared_ptr<SlimeBoss> entity = make_shared<MockSlimeBoss>(*scene.get(), 1, scene->getEventDispatcher());
			entity->setPositionX(300);
			entity->setPositionY(200);
			entity->setStatic(true);
			entity->setTotalHealth(5);
			entity->setCurrentHealth(5);

			auto spritemap = entity->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = spritemap.begin();
			while (it != spritemap.end())
			{
				entity->registerSprite(it->first, it->second);
				it++;
			}
			entity->changeToState(0);
			int health = 100;
			entity->setTotalHealth(health);
			entity->setCurrentHealth(health);
			// Act
			auto result = entity->getIsDead();
			// Assert
			Assert::IsFalse(result);
		}

		TEST_METHOD(SlimeBoss_GetIsDead_Without_Health_Should_Return_True)
		{
			// Arrange
			unique_ptr<Engine> engine = make_unique<Engine>();
			CommandBuilder commandBuilder;
			engine->start();
			engine->useCustomCommandInvoker(commandBuilder.readBindingsAndCreateInvoker());
			EventDispatcher dispatcher;

			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			savegame->setCurrentGameData(1);
			shared_ptr<SceneStateMachine> statemachine = make_shared<SceneStateMachine>(engine, savegame);
			unique_ptr<Level> scene = make_unique<Level>(1, 100, 100, engine, statemachine);

			shared_ptr<SlimeBoss> entity = make_shared<MockSlimeBoss>(*scene.get(), 1, scene->getEventDispatcher());
			entity->setPositionX(300);
			entity->setPositionY(200);
			entity->setStatic(true);
			entity->setTotalHealth(5);
			entity->setCurrentHealth(5);

			auto result = entity->buildSpritemap(1);
			map<SpriteState, shared_ptr<SpriteObject>>::iterator it = result.begin();
			while (it != result.end())
			{
				entity->registerSprite(it->first, it->second);
				it++;
			}
			entity->changeToState(0);
			// Act
			entity->setCurrentHealth(0);
			// Assert
			Assert::IsTrue(entity->getIsDead());
		}
	};
}