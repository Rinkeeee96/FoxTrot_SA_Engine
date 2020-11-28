#pragma once
class SceneStateMachine;

class GameScene : public Scene
{
public:
	GameScene(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	GameScene(const int id,const int _sceneHeight, const int _sceneWidth) : Scene(id, _sceneHeight, _sceneWidth) {};
	~GameScene() {};

	void onAttach() {};
	void start() {};
	void onDetach() {};
	void onUpdate() {};

	void registerStateMachine(SceneStateMachine * stateMachine);

protected:
	SceneStateMachine * stateMachine = nullptr;
};

