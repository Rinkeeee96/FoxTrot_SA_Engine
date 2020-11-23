#pragma once

class Game;

class GameScene : public Scene
{
public:
	GameScene(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	~GameScene() {};

	void registerGame(Game * game);

private:
	unique_ptr<Game> game;
};