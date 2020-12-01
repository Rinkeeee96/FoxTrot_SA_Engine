#pragma once
class SceneStateMachine;
class Engine;
class ICharacter;
#include "Engine/SceneManager/Scene.h"

class GameScene : public Scene
{
public:
	GameScene(const int id, Engine& _engine):
		engine(_engine), Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	GameScene(const int id,const int _sceneHeight, const int _sceneWidth, Engine& _engine) : 
		engine(_engine), Scene(id, _sceneHeight, _sceneWidth) {};
	~GameScene() {};

	// register base events
	virtual void onAttach() override = 0;
	virtual void start() override = 0;
	virtual void onUpdate() override = 0;
	virtual void onDetach() override = 0;

	void registerStateMachine(SceneStateMachine * stateMachine);
protected:
	SceneStateMachine * stateMachine;
	Engine& engine;
};

