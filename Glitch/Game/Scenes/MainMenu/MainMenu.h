#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

/// @brief Class for main menu screen
class MainMenu : public GameScene
{
public:
	MainMenu(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _sceneStateMachine) : GameScene(id, engine, _sceneStateMachine){
	};
	~MainMenu();
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	void onUpdate(float deltaTime) override;

private:
	void loadBackground();
	void loadMusic();
	void loadButtons();

	function<void(void)> onStartBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "SaveScreen";
	};

	function<void(void)> onStopBtnClick = [this]() {
		engine->setEngineRunning(false);
	};

	function<void(void)> onCreditsBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "CreditsSreen";
	};
};

inline MainMenu::~MainMenu()
{
}
