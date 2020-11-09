#include "Game.h"
#include "Levels/Builders/ILevelBuilder.h"
#include "Levels/Builders/LevelBuilderDirector.h"
#include "Levels/Builders/TestLevelBuilder.h"

void Game::run() {
	LevelBuilderDirector builderDirector;
	TestLevelBuilder testLevelBuilder = TestLevelBuilder(engine);
	builderDirector.construct(&testLevelBuilder);
	auto testLevel = testLevelBuilder.getLevel();

	engine.insertScene(testLevel);
	engine.setCurrentScene(100);
	testLevel->Start();

	engine.startTickThreads();
	while (gameRunning)
	{
		AppTickEvent60 appTick;
		AppTickEvent30 appTick30;

		engine.pollEvents();
		EventSingleton::get_instance().dispatchEvent<AppTickEvent60>(appTick);
		EventSingleton::get_instance().dispatchEvent<AppTickEvent30>(appTick30);

		this_thread::sleep_for(chrono::milliseconds(10));
	}
	engine.stopTickThreads();
}