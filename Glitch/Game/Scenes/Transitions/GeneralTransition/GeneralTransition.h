#pragma once
#include "Game/Scenes/GameScene.h"

#define TRANSITION_SCENE_DURATION_S		3

/// @brief 
class GeneralTransition : public GameScene
{
public:
	GeneralTransition(const int id) : GameScene(id) {};
	~GeneralTransition() {};

	// Inherited via Scene
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void start() override;
	virtual void onUpdate() override;

	void setNextScene(string const identifier);

private:
	void loadBackground();
	Drawable* progressBarFiller = nullptr;
	Drawable* animation = nullptr;

	bool moveCharacter = false;

	string nextScene = "";

	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point previousCallTime;
};


