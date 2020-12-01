#pragma once
class SceneStateMachine;
class Engine;
class ICharacter;

class GameScene : public Scene
{
public:
	GameScene(const int id, Engine& _engine):
		engine(_engine), Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	GameScene(const int id,const int _sceneHeight, const int _sceneWidth, Engine& _engine) : 
		engine(_engine), Scene(id, _sceneHeight, _sceneWidth) {};
	~GameScene() {};

	// register base events
	void onAttach(shared_ptr<EventDispatcher> _dispatcher) {
		// register objects in scene with event dispatcher
		//_dispatcher = shared_ptr<EventDispatcher>(new EventDispatcher());
		//dispatcher = _dispatcher;
	};

	void start() {};
	void onDetach() {};
	void onUpdate() {};

	void registerStateMachine(SceneStateMachine * stateMachine);

protected:
	SceneStateMachine * stateMachine;
	Engine& engine;
};

