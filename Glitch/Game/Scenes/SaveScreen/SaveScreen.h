#pragma once

#include "Game/Scenes/GameScene.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"


#define SPACING_INCREMENT 500

/// @brief Class for the loading saves screen
class SaveScreen : public GameScene
{
public:
	SaveScreen(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, engine, _statemachine) {};
	~SaveScreen() {};

	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	void onUpdate(float deltaTime) override;

private:
	void loadBackground();
	void loadMusic();
	void loadButtons();
	void loadText();

	function<void(void)> onSave1BtnClick = [this]() {
		savegame->setCurrentGameData(1);
		moveToNextScene = true;
		nextScene = "Overworld";
	};

	function<void(void)> onSave2BtnClick = [this]() {
		savegame->setCurrentGameData(2);
		moveToNextScene = true;
		nextScene = "Overworld";
	};

	function<void(void)> onSave3BtnClick = [this]() {
		savegame->setCurrentGameData(3);
		moveToNextScene = true;
		nextScene = "Overworld";
	};

	function<void(void)> onStopBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	function<void(void)> onSave1ExtraBtnClick = [this]() {
		resetOrSaveSaveGame(1);
	};

	function<void(void)> onSave2ExtraBtnClick = [this]() {
		resetOrSaveSaveGame(2);
	};

	function<void(void)> onSave3ExtraBtnClick = [this]() {
		resetOrSaveSaveGame(3);
	};

	void resetOrSaveSaveGame(const int id);

};

