#pragma once
#include "api.h"
#include "SceneManager/Button.h"
#include "../SceneSwitcher/SceneSwitcher.h"

class MainMenu : public Scene
{
public:
	MainMenu(const int id, SceneSwitcher _sceneSwitcher) : Scene(id), sceneSwitcher(_sceneSwitcher) {};
	~MainMenu();
	// Inherited via Scene
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void Start() override;
private:
	void LoadBackground();
	void LoadMusic();
	void LoadButtons();

	//button functions
	void OnStartBtnClick();
	void OnStopBtnClick();
	void OnCreditsBtnClick();
	void OnLoadBtnClick();
	SceneSwitcher sceneSwitcher;
};

inline MainMenu::~MainMenu()
{
}
