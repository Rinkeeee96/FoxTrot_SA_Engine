#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "sceneSwitcher/SceneSwitcher.h"

class DeadScreen : public Scene
{
public:
	DeadScreen(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH){};
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
