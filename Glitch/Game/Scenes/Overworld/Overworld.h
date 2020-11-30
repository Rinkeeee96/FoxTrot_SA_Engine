#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Levels/LoadLevelFacade.h"

/// @brief 
/// Overworld level
class Overworld : public GameScene
{
public:
	Overworld(const int id) : GameScene(id) {};
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
};

inline Overworld::~Overworld()
{
}