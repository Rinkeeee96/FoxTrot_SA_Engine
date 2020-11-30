#include "pch.h"
#include "GameScene.h"

#include "Game/Scenes/Statemachine/SceneStateMachine.h"

void GameScene::registerStateMachine(SceneStateMachine * stateMachine)
{
	this->stateMachine = stateMachine;
}
