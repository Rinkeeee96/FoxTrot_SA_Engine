#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Buttons/PrimaryButton.h"

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
	void calculateCurrentPrice();
	void updateTextBoxes();
	int currentPrice = 0;

	shared_ptr<Text> text = nullptr; 
	shared_ptr<Text> heartText2 = nullptr;

	shared_ptr<PrimaryButton> buyBTN = nullptr;

	bool handlePurchase = false;

	function<void(void)> onStopBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "Overworld";
	};

	function<void(void)> freeCoins = [this]() {
		SaveGameData save = savegame->getCurrentGameData();
		save.characterData.inventory.coins += 100;
		savegame->saveCurrentGameData(save);
		moveToNextScene = true;
		nextScene = "Shop";
	};

	function<void(void)> onShopBuyClick = [this]() {
		handlePurchase = true;
		moveToNextScene = true;
		nextScene = "Shop";
	};





};


