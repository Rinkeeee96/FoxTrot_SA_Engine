#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

class CreditsScene : public GameScene
{
public:
	CreditsScene(const int id) : GameScene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	~CreditsScene() { };
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start() override;
	void onUpdate() override;
private:
	void loadBackground();
	void loadMusic();
	void loadButtons();

	//button functions
	void onBackClick();
	void empty();
};
