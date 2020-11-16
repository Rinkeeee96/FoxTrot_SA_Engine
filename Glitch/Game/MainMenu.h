#pragma once
#include "SceneManager/Objects/Button.h"
#include "../SceneSwitcher/SceneSwitcher.h"

class MainMenu : public Scene
{
public:
	MainMenu(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH){};
	~MainMenu();
	// Inherited via Scene
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void start() override;
	virtual void onUpdate() override;
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
