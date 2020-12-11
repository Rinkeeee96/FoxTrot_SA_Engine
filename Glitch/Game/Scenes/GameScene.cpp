#include "pch.h"
#include "GameScene.h"

#include "Game/Scenes/Statemachine/SceneStateMachine.h"

/// @brief Register the savegame pointer
/// @param _savegame 
void GameScene::registerSavegame(shared_ptr<Savegame> _savegame)
{
	this->savegame = _savegame;
}
