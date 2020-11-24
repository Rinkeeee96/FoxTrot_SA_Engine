#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Levels/LoadLevelFacade.h"

/// @brief 
/// Overworld level
class Overworld : public GameScene
{
	REGISTER(Overworld);
public:
	Overworld(const int id) : GameScene(id) {};
	~Overworld();
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void onLevel1BtnClick();
	void onLevel2BtnClick();
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
	Button* stopBtn = nullptr;
};

inline Overworld::~Overworld()
{
}