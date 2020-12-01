#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class PauseScreen : public GameScene
{
public:
	PauseScreen(const int id) : GameScene(id) {};
	~PauseScreen();

	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start() override;
	void onUpdate() override;
private:
	void loadBackground();
	void loadMusic();
	void loadButtons();

	//button functions
	//void onStartBtnClick();
	//void onStopBtnClick();
	//void onCreditsBtnClick();
	//void onLoadBtnClick();
	//Button* startBtn = nullptr;
	//Button* stopBtn = nullptr;

};

