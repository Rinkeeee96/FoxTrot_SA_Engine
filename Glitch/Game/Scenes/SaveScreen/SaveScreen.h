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
	void onUpdate() override;

private:
	void loadBackground();
	void loadMusic();
	void loadButtons();
	void loadText();

	//button functions
	void onSave1BtnClick();
	void onSave2BtnClick();
	void onSave3BtnClick();
	void onStopBtnClick();

	void onSave1ExtraBtnClick();
	void onSave2ExtraBtnClick();
	void onSave3ExtraBtnClick();

	void resetOrSaveSaveGame(const int id);

};

