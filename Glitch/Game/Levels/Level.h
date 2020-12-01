#pragma once
#include "Game/Characters/Player/Player.h"
#include "Game/Scenes/GameScene.h"
/// @brief 
/// Level class. Level has all the information. 
class Level : public GameScene
{
public:
	Level(const int id, const int _sceneHeight, const int _sceneWidth, Engine& engine, map<string, string> _sounds);
	Level(const int id, const int _sceneHeight, const int _sceneWidth, Engine& engine);

	void setPlayer(Object* object);
	void setSound(map<string, string> sounds);
	void onAttach() override;
	void start() override;
	void pause();
	void onDetach() override;
	void onUpdate() override;

	shared_ptr<EventDispatcher> getEventDispatcher() { return dispatcher; }

	void setWin(const bool val) { this->win = val; }
private:
	map<string, string> sounds;
	Object* follow = nullptr;
	Player* player = nullptr;
	bool win = false;

	float startPosPlayerX = 0;
	float startPosPlayerY = 0;
};