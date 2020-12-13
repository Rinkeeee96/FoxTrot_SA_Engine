#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Levels/LoadLevelFacade.h"

/// @brief Class for overworld screen
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
	void loadSaveGame();
	void loadAchievements();

	//button functions
	void onStopBtnClick();
	void onChapterOneClick();
	void onShopBtnClick();
};

inline Overworld::~Overworld()
{
}