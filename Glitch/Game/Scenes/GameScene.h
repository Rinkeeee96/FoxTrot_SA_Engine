#pragma once
class SceneStateMachine;

class GameScene : public Scene
{
public:
	GameScene(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	GameScene(const int id,const int _sceneHeight, const int _sceneWidth) : Scene(id, _sceneHeight, _sceneWidth) {};
	~GameScene() {};

	virtual void onAttach() = 0;
	virtual void start() = 0;
	virtual void onDetach() = 0;
	virtual void onUpdate() = 0;

	void registerStateMachine(SceneStateMachine * stateMachine);

protected:
	SceneStateMachine * stateMachine;
};

