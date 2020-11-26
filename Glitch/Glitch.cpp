#pragma once
#include "pch.h"
#include "Glitch.h"
#include "Game/Game.h"

int main() {
	Game game;
	auto result = game.run();
    //if(_DEBUG) detectMemoryLeak();
	return 0;
}
