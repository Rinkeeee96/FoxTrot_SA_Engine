#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

#define SHORT_NAME_WIDTH 300
#define LONG_NAME_WIDTH 350
#define LEFT_X_CENTER 500
#define RIGHT_X_CENTER 50
#define TEXT_HEIGHT 50

/// @brief Class for credits screen
class CreditsScene : public GameScene
{
public:
	CreditsScene(const int id, unique_ptr<Engine>& _engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, _engine, _statemachine) {};
	~CreditsScene() { };
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	void onUpdate(float deltaTime) override;
private:
	vector<shared_ptr<Text>> text;

	void loadText();
	void loadBackground();
	void loadMusic();
	void loadButtons();
	void loadAnimations(); 
	void handleAnimation(float deltaTime);

	function<void(void)> onBackClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	shared_ptr<Drawable> animation = nullptr;
	bool falling = false;
};
