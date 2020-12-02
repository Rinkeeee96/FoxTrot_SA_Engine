#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class CreditsScene : public GameScene
{
public:
	CreditsScene(const int id, Engine& _engine, SceneStateMachine& _statemachine) : GameScene(id, _engine, _statemachine) {};
	~CreditsScene() { };
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start() override;
	void onUpdate() override;
private:

	vector<Text*> text;

	void loadBackground();
	void loadMusic();
	void loadButtons();

	//button functions
	void onBackClick();
	void empty();
};
