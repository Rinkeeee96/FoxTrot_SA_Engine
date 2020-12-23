#pragma once
#include "Game/Scenes/GameScene.h"

#define TRANSITION_SCENE_DURATION_S		3

/// @brief Transition Screen
class GeneralTransition : public GameScene
{
public:
	GeneralTransition(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, engine, _statemachine) {};
	~GeneralTransition() {};

	// Inherited via Scene
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void start(bool playSound) override;
	virtual void onUpdate(float deltaTime) override;

	void setNextScene(string const identifier);

private:
	void loadBackground();
	shared_ptr<Drawable> animation = nullptr;

	string nextScene = "";
	float timer = 0;
};


