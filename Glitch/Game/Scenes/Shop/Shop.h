#pragma once
#include "Game/Scenes/GameScene.h"


/// @brief Class for the shop screen
class Shop : public GameScene
{
public:
	Shop(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, engine, _statemachine) {};
	~Shop() {};

	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	void onUpdate(float deltaTime) override;

private:
	void loadBackground();
	void loadMusic();
	void loadButtons();

	function<void(void)> onStopBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "Overworld";
	};

};


