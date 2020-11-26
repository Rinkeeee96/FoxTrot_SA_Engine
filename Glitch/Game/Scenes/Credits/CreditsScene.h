#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "sceneSwitcher/SceneSwitcher.h"

class CreditsScene : public Scene
{
public:
	CreditsScene(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	~CreditsScene();
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

	Button* backBtn = nullptr;
};

inline CreditsScene::~CreditsScene()
{
}
