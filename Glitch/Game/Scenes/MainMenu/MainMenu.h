#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class MainMenu : public GameScene
{
public:
	MainMenu(const int id, Engine& engine, SceneStateMachine& _sceneStateMachine) : GameScene(id, engine, _sceneStateMachine){
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

	//button functions
	void onStartBtnClick();
	void onStopBtnClick();
	void onCreditsBtnClick();
	void onLoadBtnClick();
};

inline MainMenu::~MainMenu()
{
}
