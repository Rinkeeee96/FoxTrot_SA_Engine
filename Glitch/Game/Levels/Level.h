#pragma once
#include "Game/Scenes/GameScene.h"
#include "Commands/ICommandBuilder.h"

class Player;
/// @brief 
/// Level class. Level has all the information. 
class Level : public GameScene
{
public:
	Level(const int id, const int _sceneHeight, const int _sceneWidth, Engine& engine, SceneStateMachine& _stateMachine);

	void setPlayer(Object* object);
	void setSound(map<string, string> sounds);
	void onAttach() override;
	void start() override;
	void pause();
	void onDetach() override;
	void onUpdate() override;

	void setWin(const bool val) { this->win = val; }
private:
	map<string, string> sounds;
	Object* follow = nullptr;
	Player* player = nullptr;
	bool win = false;

	ICommandBuilder* commandBuilder;

	float startPosPlayerX = 0;
	float startPosPlayerY = 0;
};