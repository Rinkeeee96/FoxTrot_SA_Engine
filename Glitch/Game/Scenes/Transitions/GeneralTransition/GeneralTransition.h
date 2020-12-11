#pragma once
#include "Game/Scenes/GameScene.h"

#define TRANSITION_SCENE_DURATION_S		3

/// @brief 
class GeneralTransition : public GameScene
{
public:
	GeneralTransition(const int id, Engine& engine, SceneStateMachine& _statemachine) : GameScene(id, engine, _statemachine) {};
	~GeneralTransition() {};

	// Inherited via Scene
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void start(bool playSound) override;
	virtual void onUpdate(float deltaTime) override;

	void setNextScene(string const identifier);

private:
	void loadBackground();
	Drawable* progressBarFiller = nullptr;
	Drawable* animation = nullptr;

	bool moveCharacter = false;

	string nextScene = "";

	float timer = 0;
};


