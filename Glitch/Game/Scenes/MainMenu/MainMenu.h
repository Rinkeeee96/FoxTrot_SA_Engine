#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class MainMenu : public GameScene
{
public:
	MainMenu(const int id, Engine& engine) : GameScene(id,engine){};
	~MainMenu();
	// Inherited via Scene
	void onAttach(shared_ptr<EventDispatcher> _dispatcher) override;
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
};

inline MainMenu::~MainMenu()
{
}
