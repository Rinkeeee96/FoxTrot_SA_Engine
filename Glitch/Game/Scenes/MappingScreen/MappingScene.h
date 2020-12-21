#pragma once
#include "Game/Scenes/GameScene.h"

class MappingScene : public GameScene
{
public:
	MappingScene(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, engine, _statemachine) {};
	~MappingScene() {};

private:

};
