#pragma once
#include "api.h"
#include "../../../../SceneSwitcher/SceneSwitcher.h"

#define TRANSITION_SCENE_DURATION_S		3


class GeneralTransition : public Scene
{
public:
	GeneralTransition(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	~GeneralTransition() {};

	// Inherited via Scene
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void Start() override;
	virtual void run() override;
private:
	void LoadBackground();
	Drawable* animation = nullptr;

	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point previousCallTime;
};


