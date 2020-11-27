#pragma once

#include "Game/Scenes/GameScene.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"



class SaveScreen : public GameScene
{
public:
	SaveScreen(const int id) : GameScene(id) {};
	~SaveScreen() {};

	// Inherited via Scene
	void onAttach() override;
	void onDetach() override;
	void start() override;
	void onUpdate() override;

private:
	void loadBackground();
	void loadMusic();
	void loadButtons();

	//button functions
	void onSave1BtnClick();
	void onSave2BtnClick();
	void onSave3BtnClick();
	void onStopBtnClick();

};

