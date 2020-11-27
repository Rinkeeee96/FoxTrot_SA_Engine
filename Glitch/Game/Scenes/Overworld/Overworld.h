#pragma once
#include "SceneSwitcher/SceneSwitcher.h"
#include "Game/Levels/LoadLevelFacade.h"

/// @brief 
/// Overworld level
class Overworld : public Scene
{
public:
	Overworld(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
	~Overworld();
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void onLevel1BtnClick();
	void onLevel2BtnClick();
	void onLevel3BtnClick();
	void start() override;
	virtual void onUpdate() override;

private:
	void loadBackground();
	void loadMusic();
	void loadButtons();

	//button functions
	void onStartBtnClick();
	void onStopBtnClick();
	void onCreditsBtnClick();
	void onLoadBtnClick();
	Button* level1Btn = nullptr;
	Button* level1TextBtn = nullptr;
	Button* level2Btn = nullptr;
	Button* level2TextBtn = nullptr;
	Button* level3Btn = nullptr;
	Button* level3TextBtn = nullptr;

	Button* stopBtn = nullptr;
};

inline Overworld::~Overworld()
{
}