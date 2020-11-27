#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class DeathScreen : public GameScene
{
public:
	DeathScreen(const int id) : GameScene(id) {};
	~DeathScreen();
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
};

inline DeathScreen::~DeathScreen()
{
}
