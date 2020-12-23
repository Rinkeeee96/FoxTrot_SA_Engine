#pragma once
class Savegame;

class SceneStateMachine;
class Engine;
class ICharacter;
#include "Engine/SceneManager/Scene.h"

/// @brief Base class for game scenes, derived from engine scene
class GameScene : public Scene
{
public:
	GameScene(const int id, unique_ptr<Engine>& _engine, shared_ptr<SceneStateMachine> _sceneStateMachine):
		engine(_engine), stateMachine(_sceneStateMachine), Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	GameScene(const int id, const int _sceneHeight, const int _sceneWidth, unique_ptr<Engine>& _engine, shared_ptr<SceneStateMachine> _sceneStateMachine) :
		engine(_engine), stateMachine(_sceneStateMachine), Scene(id, _sceneHeight, _sceneWidth) {};

	// register base events
	virtual void onAttach() override = 0;
	virtual void start(bool playSound) override = 0;
	virtual void onUpdate(float deltaTime) override = 0;
	virtual void onDetach() override = 0;

	unique_ptr<Engine>& getEngine() { return this->engine; }
	void registerSavegame(shared_ptr<Savegame> _savegame);
protected:
	shared_ptr<SceneStateMachine> stateMachine;
	unique_ptr<Engine>& engine;
	shared_ptr<Savegame> savegame;

	bool moveToNextScene = false;
	string nextScene;
	bool useTransition = false;
	bool playSound = false;
};

