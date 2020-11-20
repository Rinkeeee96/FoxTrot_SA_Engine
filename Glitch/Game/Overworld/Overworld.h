#pragma once
#include "SceneSwitcher/SceneSwitcher.h"
#include "Game/Levels/LoadLevelFacade.h"

/// @brief 
/// Overworld level
class Overworld : public Scene
{
public:
	Overworld(const int id, Engine& _engine) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH), engine(_engine) {};
	~Overworld();
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start() override;
	virtual void onUpdate() override;

private:
	Engine& engine;

	void loadBackground();
	void loadMusic();
	void loadButtons();

	//button functions
	void onStopBtnClick();
	void onLevel1BtnClick();
	void onLevel2BtnClick();
};

inline Overworld::~Overworld()
{
}