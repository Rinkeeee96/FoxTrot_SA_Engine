#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Levels/LoadLevelFacade.h"

/// @brief 
/// Overworld level
class Overworld : public GameScene
{
public:
	Overworld(const int id, Engine& engine, SceneStateMachine& _statemachine) : GameScene(id, engine, _statemachine) {};
	~Overworld();
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void onLevel1BtnClick();
	void onLevel2BtnClick();
	void onLevel3BtnClick();
	void start(bool playSound) override;
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
	void onChapterOneClick();
	void onShopBtnClick();
};

inline Overworld::~Overworld()
{
}