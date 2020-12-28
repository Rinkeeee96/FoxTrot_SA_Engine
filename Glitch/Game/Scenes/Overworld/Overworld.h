#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Levels/LoadLevelFacade.h"

/// @brief Class for overworld screen
class Overworld : public GameScene
{
public:
	Overworld(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, engine, _statemachine) {};
	~Overworld();
	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	virtual void onUpdate(float deltaTime) override;

private:
	void loadBackground();
	void loadMusic();
	void loadButtons();
	void loadSaveGame();
	void loadAchievements();

	function<void(void)> onLevel1BtnClick = [this]() {
		moveToNextScene = true;
		useTransition = true;
		nextScene = "Level_1";
	};

	function<void(void)> onLevel2BtnClick = [this]() {
		moveToNextScene = true;
		useTransition = true;
		nextScene = "Level_2";
	};

	function<void(void)> onLevel3BtnClick = [this]() {
		moveToNextScene = true;
		useTransition = true;
		nextScene = "Level_3";
	};
	function<void(void)> onLevel4BtnClick = [this]() {
		moveToNextScene = true;
		useTransition = true;
		nextScene = "Level_4";
	};
	function<void(void)> onLevel5BtnClick = [this]() {
		moveToNextScene = true;
		useTransition = true;
		nextScene = "Level_5";
	};

	function<void(void)> onStopBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	function<void(void)> onChapterOneClick = [this]() {
		moveToNextScene = true;
		nextScene = "ChapterOne";
	};
	function<void(void)> onChapterTwoClick = [this]() {
		moveToNextScene = true;
		nextScene = "ChapterTwo";
	};
	function<void(void)> onChapterThreeClick = [this]() {
		moveToNextScene = true;
		nextScene = "ChapterThree";
	};

	function<void(void)> onShopBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "Shop";
	};
};

inline Overworld::~Overworld()
{
}