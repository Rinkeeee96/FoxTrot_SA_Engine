#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class DeathScreen : public GameScene
{
public:
	DeathScreen(const int id, Engine& engine) : GameScene(id, engine) {};
	~DeathScreen();
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
	void onReStartBtnClick();
	void onOverworldBtnClick();
};

inline DeathScreen::~DeathScreen()
{
}
