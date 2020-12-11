#pragma once
class Savegame;

class SceneStateMachine;
class Engine;
class ICharacter;
#include "Engine/SceneManager/Scene.h"


class GameScene : public Scene
{
public:
	GameScene(const int id, Engine& _engine, SceneStateMachine& _sceneStateMachine):
		engine(_engine), stateMachine(_sceneStateMachine), Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	GameScene(const int id, const int _sceneHeight, const int _sceneWidth, Engine& _engine, SceneStateMachine& _sceneStateMachine) :
		engine(_engine), stateMachine(_sceneStateMachine), Scene(id, _sceneHeight, _sceneWidth) {};

	// register base events
	virtual void onAttach() override = 0;
	virtual void start(bool playSound) override = 0;
	virtual void onUpdate(float deltaTime) override = 0;
	virtual void onDetach() override = 0;

	void registerSavegame(shared_ptr<Savegame> _savegame);
protected:
	SceneStateMachine& stateMachine;
	Engine& engine;
	shared_ptr<Savegame> savegame;
};

