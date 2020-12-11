#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

#define SHORT_NAME_WIDTH 300
#define LONG_NAME_WIDTH 350
#define LEFT_X_CENTER 500
#define RIGHT_X_CENTER 50
#define TEXT_HEIGHT 50

/// @brief Class for credits screen
class CreditsScene : public GameScene
{
public:
	CreditsScene(const int id, Engine& _engine, SceneStateMachine& _statemachine) : GameScene(id, _engine, _statemachine) {};
	~CreditsScene() { };
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	void onUpdate() override;
private:
	vector<Text*> text;

	void loadText();
	void loadBackground();
	void loadMusic();
	void loadButtons();

	//button functions
	void onBackClick();
	void empty();
};
