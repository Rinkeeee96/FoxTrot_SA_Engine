#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class DeadScreen : public GameScene
{
public:
	DeadScreen(const int id) : GameScene(id) {};
	~DeadScreen();
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
	void onReStartBtnClick();
	void onOverworldBtnClick();
	
	Button* startBtn = nullptr;
	Button* mainBtn = nullptr;
};

inline DeadScreen::~DeadScreen()
{
}
