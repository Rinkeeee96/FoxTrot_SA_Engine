#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

/// @brief Class for main menu screen
class MainMenu : public GameScene
{
public:
	MainMenu(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _sceneStateMachine) : GameScene(id, engine, _sceneStateMachine){};
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

	bool playMusicCredits = false;

	function<void(void)> onStartBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "SaveScreen";
	};

	function<void(void)> onStopBtnClick = [this]() {
		engine->setEngineRunning(false);
	};

	function<void(void)> onMappingBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MappingScreen";
	};

	function<void(void)> onCreditsBtnClick = [this]() {
		playMusicCredits = true;
		moveToNextScene = true;
		nextScene = "CreditsSreen";
	};

	function<void(void)> onInfoBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "GameInfo";
	};
};

inline MainMenu::~MainMenu()
{
}
