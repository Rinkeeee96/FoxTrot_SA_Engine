#pragma once

#include "SceneSwitcher/SceneSwitcher.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"



class SaveScreen : public Scene
{
public:
	SaveScreen(const int id) : Scene(id, WINDOW_HEIGHT, WINDOW_WIDTH) {};
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

