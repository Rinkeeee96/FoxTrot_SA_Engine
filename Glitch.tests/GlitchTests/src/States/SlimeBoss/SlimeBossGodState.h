#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Commands/Builder/CommandBuilder.h>
#include <Game/Scenes/Statemachine/SceneStateMachine.h>
#include <GlitchTests/src/mocks/MockSlimeBoss.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	TEST_CLASS(StatesTests)
	{
	public:
		TEST_METHOD(SlimeBossDamageCooldown_Should_Set_Invincible)
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
			entity->setCanJump(false);
			entity->setTotalHealth(5);
			entity->setCurrentHealth(3);
			entity->getStateMachine().changeState(make_unique<SlimeBossNormalState>(), *entity);
			// Act
			entity->onUpdate(1);
			// Assert
			Assert::IsTrue(entity->getInvincible());
		}

		TEST_METHOD(SlimeBossDamageCooldownState_More_Than_One_Second_Should_Change_To_NormalState)
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
			entity->setCanJump(false);
			entity->setTotalHealth(5);
			entity->setCurrentHealth(3);
			// Act
			entity->getStateMachine().changeState(make_unique<SlimeBossNormalState>(), *entity);
			entity->onUpdate(1);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			entity->onUpdate(1);
			// Assert
			IState<SlimeBoss>& result = entity->getStateMachine().getCurrentState();
			// Assert
			if (typeid(SlimeBossNormalState) == typeid(result)) {
				Assert::IsTrue(true);
			}
			else {
				Assert::IsTrue(false);
			}
		}

		//TEST_METHOD(DamageCooldownState_Less_Than_One_Second_Should_Keep_DamageCooldownState)
		//{
		//	// Arrange
		//	EventDispatcher dispatcher;
		//	Player player{ 2, dispatcher };
		//	player.setCanJump(false);
		//	player.setTotalHealth(5);
		//	player.setInvincible(true);
		//	chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
		//	// Act

		//	player.getStateMachine().changeState(make_unique<DamageCooldownState>(), player);
		//	player.onUpdate(1);

		//	chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
		//	std::chrono::milliseconds miliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		//	std::chrono::milliseconds ml{ 900 };
		//	std::this_thread::sleep_for(std::chrono::milliseconds(ml - miliSeconds));
		//	player.onUpdate(1);
		//	// Assert
		//	IState<Player>& result = player.getStateMachine().getCurrentState();
		//	// Assert
		//	if (typeid(DamageCooldownState) == typeid(result)) {
		//		Assert::IsTrue(true);
		//	}
		//	else {
		//		Assert::IsTrue(false);
		//	}
		//}
	};
}