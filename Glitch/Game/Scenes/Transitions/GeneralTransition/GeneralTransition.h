#pragma once

#define TRANSITION_SCENE_DURATION_S		3

/// @brief 
class GeneralTransition : public Scene
{
public:
	GeneralTransition(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	~GeneralTransition() {};

	// Inherited via Scene
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void start() override;
	virtual void onUpdate() override;

private:
	void loadBackground();
	Drawable* progressBarFiller = nullptr;
	Drawable* animation = nullptr;

	bool moveCharacter = false;

	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point previousCallTime;
};


