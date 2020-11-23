#include "pch.h"
#include "GameScene.h"

void GameScene::registerGame(Game * game)
{
	this->game = unique_ptr<Game>(game);
}
