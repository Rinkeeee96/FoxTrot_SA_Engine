#pragma once
#include "Game/Scenes/GameScene.h"

// Prices


#define HEALTH_PRICE 50



class Player;

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

	shared_ptr<Text> text;

	bool handlePurchase = false;

	function<void(void)> onStopBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "Overworld";
	};

	function<void(void)> doSomethingYouStupidCunt = [this]() {
		cout << "Button called" << endl;
		handlePurchase = true;
		moveToNextScene = true;
		nextScene = "Shop";
	};





};


