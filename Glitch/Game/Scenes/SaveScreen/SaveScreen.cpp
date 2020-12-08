#include "pch.h"
#include "SaveScreen.h"
#include "Game/Game.h"

#define BIND_FN(function) std::bind(&SaveScreen::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

void SaveScreen::onAttach()
{
	
	loadButtons();
	loadBackground();
	loadMusic();

}

void SaveScreen::onDetach()
{
	Scene::onDetach();
}

void SaveScreen::start(bool playSound)
{
	if(playSound)engine.getSoundEngine().onStartBackgroundMusicEvent("MENU_SOUND");
}

void SaveScreen::onUpdate()
{
}

void SaveScreen::loadBackground()
{
	SpriteObject* BG_LAYER_0 = new SpriteObject(-999, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(-998, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(-997, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");

	auto* layer0 = new Drawable(-992);
	layer0->setStatic(true);
	layer0->setPositionX(1);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* animation = new Drawable(-991);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	auto* layer2 = new Drawable(-990);
	layer2->setStatic(true);
	layer2->setPositionX(1);
	layer2->setPositionY(1080);
	layer2->setWidth(1920);
	layer2->setHeight(1080);
	layer2->registerSprite(SpriteState::DEFAULT, BG_LAYER_2);
	layer2->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0, false, true);
	addNewObjectToLayer(1, animation, false, true);
	addNewObjectToLayer(2, layer2, false, true);
}

void SaveScreen::loadMusic()
{
	engine.getSoundEngine().onLoadBackgroundMusicEvent("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav");
}

void SaveScreen::loadButtons()
{
	string nameBtn = "Empty";
	string nameBtnExtra = "Create New";
	if (!savegame->isSaveGameDataEmpty(1))
	{
		nameBtn = savegame->getSaveGameData(1).saveGameName + " Progress: " + to_string(savegame->getSaveGameData(1).getOverWorldProgress()) + " %";
		nameBtnExtra = "Delete";
	}

	auto* save1 = new PrimaryButton(-996, nameBtn, BIND_FN(onSave1BtnClick), this->dispatcher);
	save1->setPositionX(CENTER_X - save1->getWidth() / 2 - 110);
	save1->setPositionY(CENTER_Y - save1->getHeight() / 2);
	if (savegame->isSaveGameDataEmpty(1)) save1->disable();

	auto* delSave1 = new PrimaryButton(-992, nameBtnExtra, BIND_FN(onSave1ExtraBtnClick), this->dispatcher);
	delSave1->setPositionX(CENTER_X - save1->getWidth() / 2 + 110);
	delSave1->setPositionY(CENTER_Y - save1->getHeight() / 2);

	string name1Btn = "Empty";
	string name1BtnExtra = "Create New";
	if (!savegame->isSaveGameDataEmpty(2))
	{
		name1Btn = savegame->getSaveGameData(2).saveGameName + " Progress: " + to_string(savegame->getSaveGameData(2).getOverWorldProgress()) + " %";
		name1BtnExtra = "Delete";
	}

	auto* save2 = new PrimaryButton(-995, name1Btn, BIND_FN(onSave2BtnClick), this->dispatcher);
	save2->setPositionX(CENTER_X - save2->getWidth() / 2 - 110);
	save2->setPositionY(CENTER_Y - save2->getHeight() / 2 + 100);
	if (savegame->isSaveGameDataEmpty(2)) save2->disable();

	auto* delSave2 = new PrimaryButton(-991, name1BtnExtra, BIND_FN(onSave2ExtraBtnClick), this->dispatcher);
	delSave2->setPositionX(CENTER_X - save1->getWidth() / 2 + 110);
	delSave2->setPositionY(CENTER_Y - save1->getHeight() / 2 + 100);

	string name2Btn = "Empty";
	string name3BtnExtra = "Create New";
	if (!savegame->isSaveGameDataEmpty(3))
	{
		name2Btn = savegame->getSaveGameData(3).saveGameName + " Progress: " + to_string(savegame->getSaveGameData(3).getOverWorldProgress()) + " %";
		name3BtnExtra = "Delete";
	}

	auto* save3 = new PrimaryButton(-994, name2Btn, BIND_FN(onSave3BtnClick), this->dispatcher);
	save3->setPositionX(CENTER_X - save3->getWidth() / 2 - 110);
	save3->setPositionY(CENTER_Y - save3->getHeight() / 2 + 200);
	if (savegame->isSaveGameDataEmpty(3)) save3->disable();

	auto* delSave3 = new PrimaryButton(-990, name3BtnExtra, BIND_FN(onSave3ExtraBtnClick), this->dispatcher);
	delSave3->setPositionX(CENTER_X - save1->getWidth() / 2 + 110);
	delSave3->setPositionY(CENTER_Y - save1->getHeight() / 2 + 200);

	auto* stopBtn = new SecondaryButton(-993, "To Main Menu", BIND_FN(onStopBtnClick), this->dispatcher);
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, save1);
	addNewObjectToLayer(3, delSave1);
	addNewObjectToLayer(3, delSave2);
	addNewObjectToLayer(3, delSave3);

	addNewObjectToLayer(3, save2);
	addNewObjectToLayer(3, save3);
	addNewObjectToLayer(3, stopBtn);
}

void SaveScreen::onSave1BtnClick()
{
	savegame->setCurrentGameData(1);
	stateMachine.switchToScene("Overworld", true);
}

void SaveScreen::resetOrSaveSaveGame(const int id)
{
	if (savegame->isSaveGameDataEmpty(id))
	{
		SaveGameData save;
		save.saveGameName = "Save " + to_string(id);
		savegame->addSaveGameData(id, save);
		stateMachine.switchToScene("SaveScreen", false, false);
	}
	else
	{
		savegame->deleteSaveGameData(id);
		stateMachine.switchToScene("SaveScreen", false, false);
	}
}

void SaveScreen::onSave1ExtraBtnClick()
{
	resetOrSaveSaveGame(1);
}

void SaveScreen::onSave2BtnClick()
{
	savegame->setCurrentGameData(2);
	stateMachine.switchToScene("Overworld", true);
}

void SaveScreen::onSave2ExtraBtnClick()
{
	resetOrSaveSaveGame(2);
}


void SaveScreen::onSave3BtnClick()
{
	savegame->setCurrentGameData(3);
	stateMachine.switchToScene("Overworld", true);
}

void SaveScreen::onSave3ExtraBtnClick()
{
	resetOrSaveSaveGame(3);
}


void SaveScreen::onStopBtnClick() {
	stateMachine.switchToScene("MainMenu",false);
}