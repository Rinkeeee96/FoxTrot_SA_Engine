#pragma once
#include "api.h"
#include "SceneManager/Button.h"
#include "../SceneSwitcher/SceneSwitcher.h"

class MainMenu : public Scene
{
public:
	MainMenu(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH){};
	~MainMenu();
	// Inherited via Scene
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void Start() override;
	virtual void run() override;
private:
	void LoadBackground();
	void LoadMusic();
	void LoadButtons();

	//button functions
	void OnStartBtnClick();
	void OnStopBtnClick();
	void OnCreditsBtnClick();
	void OnLoadBtnClick();
};

inline MainMenu::~MainMenu()
{
}
