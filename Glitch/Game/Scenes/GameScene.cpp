#include "pch.h"
#include "GameScene.h"

#include "Game/Scenes/Statemachine/SceneStateMachine.h"

void GameScene::registerSavegame(shared_ptr<Savegame> _savegame)
{
	this->savegame = _savegame;
}
