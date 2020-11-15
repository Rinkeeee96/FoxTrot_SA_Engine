#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "../../SceneSwitcher/SceneSwitcher.h"

class DeadScreen : public Scene
{
public:
	DeadScreen(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH){};
	~DeadScreen();
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

inline DeadScreen::~DeadScreen()
{
}
