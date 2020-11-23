#include "pch.h"
#include "GameScene.h"

#include "Game/Game.h"

void GameScene::registerGame(Game * game)
{
	this->game = game;
}
