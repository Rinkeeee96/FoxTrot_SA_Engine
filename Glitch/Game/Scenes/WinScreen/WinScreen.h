#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class WinScreen : public GameScene
{
public:
	WinScreen(const int id, Engine& engine, SceneStateMachine& _statemachine) : GameScene(id, engine, _statemachine) {};
	~WinScreen();
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	void onUpdate() override;
private:
	void LoadBackground();
	void LoadMusic();
	void LoadButtons();

	//button functions
	void OnMainBtnClick();
	void onOverworldBtnClick();

	int animationTick = 0;
	Drawable* animation = nullptr;
};

inline WinScreen::~WinScreen()
{
}
