#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class WinScreen : public GameScene
{
	REGISTER(WinScreen);

public:
	WinScreen(const int id) : GameScene(id) {};
	~WinScreen();
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start() override;
	void onUpdate() override;
private:
	void LoadBackground();
	void LoadMusic();
	void LoadButtons();

	//button functions
	void OnMainBtnClick();
	void onOverworldBtnClick();

	int animationTick = 0;
	Drawable* animation = nullptr;
	Button* overBtn = nullptr;
	Button* mainBtn = nullptr;
};

inline WinScreen::~WinScreen()
{
}
