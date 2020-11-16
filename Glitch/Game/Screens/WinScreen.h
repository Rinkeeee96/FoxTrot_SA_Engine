#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "../../SceneSwitcher/SceneSwitcher.h"

class WinScreen : public Scene
{
public:
	WinScreen(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	~WinScreen();
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
	void OnMainBtnClick();
};

inline WinScreen::~WinScreen()
{
}
