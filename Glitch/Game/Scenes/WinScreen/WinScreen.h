#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

/// @brief Class for the win screen
class WinScreen : public GameScene
{
public:
	WinScreen(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, engine, _statemachine) {};
	~WinScreen();
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	void onUpdate(float deltaTime) override;
private:
	void LoadBackground();
	void LoadMusic();
	void LoadButtons();

	function<void(void)> OnMainBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	function<void(void)> onOverworldBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "Overworld";
	};
	bool falling = false;
	int animationTick = 0;
	shared_ptr<Drawable> animation = nullptr;
};

inline WinScreen::~WinScreen()
{
}
