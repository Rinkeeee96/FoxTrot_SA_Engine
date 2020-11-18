#pragma once

#define TRANSITION_SCENE_DURATION_S		3

/// @brief 
class GeneralTransition : public Scene
{
public:
	GeneralTransition(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	~GeneralTransition() {};

	// Inherited via Scene
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void Start() override;
	virtual void update() override;

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


