#include "Game.h"

void Game::run() {
	LevelBuilderDirector builderDirector;

	LevelBuilder levelOneBuilder = LevelBuilder(engine);
	builderDirector.construct(&levelOneBuilder);
	auto levelOne = levelOneBuilder.getLevel();
	//levelOne->start();
	engine.setCurrentScene(levelOne->getSceneID());

	engine.startTickThreads();
	while (gameRunning)
	{
		AppTickEvent60 appTick;
		AppTickEvent30 appTick30;

		engine.pollEvents();
		EventSingleton::get_instance().dispatchEvent<AppTickEvent60>(appTick);
		EventSingleton::get_instance().dispatchEvent<AppTickEvent30>(appTick30);

		for (Object* obj : engine.getCurrentScene()->getAllObjectsInScene())
		{
			obj->onUpdate();
		}

		this_thread::sleep_for(chrono::milliseconds(10));
	}
	engine.stopTickThreads();
}