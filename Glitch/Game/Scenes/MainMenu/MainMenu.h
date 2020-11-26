#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "SceneSwitcher/SceneSwitcher.h"

class MainMenu : public Scene
{
public:
	MainMenu(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH){};
	~MainMenu();
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
	void onStartBtnClick();
	void onStopBtnClick();
	void onCreditsBtnClick();
	void onLoadBtnClick();
	Button* startBtn = nullptr;
	Button* stopBtn = nullptr; 
	Button* creditsBtn = nullptr;
};

inline MainMenu::~MainMenu()
{
}
