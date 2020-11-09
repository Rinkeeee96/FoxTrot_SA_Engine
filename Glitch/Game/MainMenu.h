#pragma once
#include "api.h"
#include "SceneManager/Button.h"

class MainMenu : public Scene
{
public:
	MainMenu() : Scene(1) {};
	~MainMenu();
private:
	vector<Button> buttons;

	// Inherited via Scene
	virtual void OnAttach() override;
	virtual void Start() override;
	virtual void OnDetach() override;

	void OnStartBtnClick();
};

inline MainMenu::~MainMenu()
{
}
