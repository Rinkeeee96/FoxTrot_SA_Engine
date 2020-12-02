#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

class PauseScreen : public GameScene
{
public:
	PauseScreen(const int id, Engine& engine, SceneStateMachine& _statemachine) : GameScene(id, engine, _statemachine) {};
	~PauseScreen() {};

	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start() override;
	void onUpdate() override;
private:
	void loadBackground();
	void loadButtons();
	void loadMusic();

	//button functions
	void onResumeButtonClick();
	void onExitButtonClick();
	void onMusicButtonClick();
	void onHelpButtonClick();
};

