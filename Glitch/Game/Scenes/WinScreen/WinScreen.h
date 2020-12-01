#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class WinScreen : public GameScene
{
public:
	WinScreen(const int id, Engine& engine) : GameScene(id, engine) {};
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
};

inline WinScreen::~WinScreen()
{
}
