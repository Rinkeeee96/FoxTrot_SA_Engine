#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "SceneSwitcher/SceneSwitcher.h"

class WinScreen : public Scene
{
public:
	WinScreen(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
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
