#pragma once
#include "api.h"
#include "../../SceneSwitcher/SceneSwitcher.h"


class TransitionScene : public Scene
{
public:
	TransitionScene(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	~TransitionScene() {};

	// Inherited via Scene
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void Start() override;
	virtual void run() override;
private:
	void LoadBackground();
};



