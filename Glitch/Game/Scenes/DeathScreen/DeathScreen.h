#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

/// @brief Class for the death screen
class DeathScreen : public GameScene
{
public:
	DeathScreen(const int id, Engine& engine, SceneStateMachine& _statemachine) : GameScene(id, engine, _statemachine) {};
	~DeathScreen();
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	void onUpdate(float deltaTime) override;
private:
	void loadBackground();
	void loadMusic();
	void loadButtons();

	//button functions
	void onReStartBtnClick();
	void onOverworldBtnClick();
};

inline DeathScreen::~DeathScreen()
{
}
