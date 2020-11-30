#pragma once
class SceneStateMachine;
class Engine;

class GameScene : public Scene
{
public:
	GameScene(const int id, Engine& _engine) : engine(_engine), Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	GameScene(const int id,const int _sceneHeight, const int _sceneWidth, Engine& _engine) : engine(_engine), Scene(id, _sceneHeight, _sceneWidth) {};
	~GameScene() {};

	void onAttach() {};
	void start() {};
	void onDetach() {};
	void onUpdate() {};

	void registerStateMachine(SceneStateMachine * stateMachine);

protected:
	SceneStateMachine * stateMachine;
	Engine& engine;
};

