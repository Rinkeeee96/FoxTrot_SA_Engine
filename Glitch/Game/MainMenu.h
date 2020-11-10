#pragma once
#include "api.h"
#include "SceneManager/Button.h"

class MainMenu : public Scene
{
public:
	MainMenu() : Scene(1) {};
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
};

inline MainMenu::~MainMenu()
{
}
