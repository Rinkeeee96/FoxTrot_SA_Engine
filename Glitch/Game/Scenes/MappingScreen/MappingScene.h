#pragma once
#include "Game/Scenes/GameScene.h"

class MappingScene : public GameScene
{
public:
	MappingScene(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, engine, _statemachine) {};
	~MappingScene() {};

	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	virtual void onUpdate(float deltaTime) override;

private:
	void loadBackground();
	void loadMusic();
	void loadButtons();
	void loadSaveGame();

	function<void(void)> onStopBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};
};
