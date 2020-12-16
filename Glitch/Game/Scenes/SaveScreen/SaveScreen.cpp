#include "pch.h"
#include "SaveScreen.h"
#include "Game/Game.h"

#define BIND_FN(function) std::bind(&SaveScreen::function, *this)

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

/// @brief 
/// Loadbuttons
/// LoadBackground
/// LoadMusic
void SaveScreen::onAttach()
{
	
	loadButtons();
	loadBackground();
	loadMusic();
	loadText();

}

/// @brief 
/// Remove the sounds of the soundengine
void SaveScreen::onDetach()
{
	Scene::onDetach();
}

/// @brief 
/// Create the sounds for this scene
void SaveScreen::start(bool playSound)
{
	if(playSound)engine.startSound("MENU_SOUND");
}

/// @brief
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void SaveScreen::onUpdate(float deltaTime)
{
}

/// @brief 
/// Loads the background
void SaveScreen::loadBackground()
{
	SpriteObject* BG_LAYER_0 = new SpriteObject(-999, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png");
	SpriteObject* BG_LAYER_ADVENTRUE = new SpriteObject(-998, 37, 50, 6, 300, "Assets/Sprites/Character/adventure_run_right.png");
	SpriteObject* BG_LAYER_2 = new SpriteObject(-997, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png");
	SpriteObject* emptyBlock = new SpriteObject(-996, 309, 253, 1, 300, "Assets/Inventory/text_background.png");

	auto* layer0 = new Drawable(-992);
	layer0->setStatic(true);
	layer0->setPositionX(0);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	auto* block1 = new Drawable(-991);
	block1->setStatic(true);
	block1->setPositionX(550);
	block1->setPositionY(825);
	block1->setWidth(300);
	block1->setHeight(500);
	block1->registerSprite(SpriteState::DEFAULT, emptyBlock);
	block1->changeToState(SpriteState::DEFAULT);

	auto* block2 = new Drawable(-990);
	block2->setStatic(true);
	block2->setPositionX(1050);
	block2->setPositionY(825);
	block2->setWidth(300);
	block2->setHeight(500);
	block2->registerSprite(SpriteState::DEFAULT, emptyBlock);
	block2->changeToState(SpriteState::DEFAULT);

	auto* block3 = new Drawable(-989);
	block3->setStatic(true);
	block3->setPositionX(1550);
	block3->setPositionY(825);
	block3->setWidth(300);
	block3->setHeight(500);
	block3->registerSprite(SpriteState::DEFAULT, emptyBlock);
	block3->changeToState(SpriteState::DEFAULT);

	auto* animation = new Drawable(-988);
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(500);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	auto* layer2 = new Drawable(-987);
	layer2->setStatic(true);
	layer2->setPositionX(0);
	layer2->setPositionY(1080);
	layer2->setWidth(1920);
	layer2->setHeight(1080);
	layer2->registerSprite(SpriteState::DEFAULT, BG_LAYER_2);
	layer2->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, layer0, false, true);
	addNewObjectToLayer(1, animation, false, true);
	addNewObjectToLayer(2, layer2, false, true);
	addNewObjectToLayer(3, block1, false, true);
	addNewObjectToLayer(3, block2, false, true);
	addNewObjectToLayer(3, block3, false, true);
}

/// @brief 
/// Load the sounds for this scene
void SaveScreen::loadMusic()
{
	engine.loadSound("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav");
}

/// @brief 
/// Loads all the buttons in the Overworld
void SaveScreen::loadButtons()
{
	string nameBtnExtra = "Create New";
	if (!savegame->isSaveGameDataEmpty(1))
	{
		auto* save1 = new PrimaryButton(-996, "Start!", BIND_FN(onSave1BtnClick), this->dispatcher);
		save1->setPositionX(605);
		save1->setPositionY(750);
		addNewObjectToLayer(4, save1);
		nameBtnExtra = "Delete";
	}

	auto* delSave1 = new PrimaryButton(-992, nameBtnExtra, BIND_FN(onSave1ExtraBtnClick), this->dispatcher);
	delSave1->setPositionX(605);
	delSave1->setPositionY(805);

	nameBtnExtra = "Create New";
	if (!savegame->isSaveGameDataEmpty(2))
	{
		auto* save1 = new PrimaryButton(-995, "Start!", BIND_FN(onSave2BtnClick), this->dispatcher);
		save1->setPositionX(605 + SPACING_INCREMENT);
		save1->setPositionY(750);
		addNewObjectToLayer(4, save1);
		nameBtnExtra = "Delete";
	}

	auto* delSave2 = new PrimaryButton(-991, nameBtnExtra, BIND_FN(onSave2ExtraBtnClick), this->dispatcher);
	delSave2->setPositionX(605 + SPACING_INCREMENT);
	delSave2->setPositionY(805);

	nameBtnExtra = "Create New";
	if (!savegame->isSaveGameDataEmpty(3))
	{
		auto* save1 = new PrimaryButton(-994, "Start!", BIND_FN(onSave3BtnClick), this->dispatcher);
		save1->setPositionX(605 + SPACING_INCREMENT*2);
		save1->setPositionY(750);
		addNewObjectToLayer(4, save1);
		nameBtnExtra = "Delete";
	}

	auto* delSave3 = new PrimaryButton(-990, nameBtnExtra, BIND_FN(onSave3ExtraBtnClick), this->dispatcher);
	delSave3->setPositionX(605 + SPACING_INCREMENT*2);
	delSave3->setPositionY(805);

	auto* stopBtn = new SecondaryButton(-993, "To Main Menu", BIND_FN(onStopBtnClick), this->dispatcher);
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	
	addNewObjectToLayer(4, delSave1);
	addNewObjectToLayer(4, delSave2);
	addNewObjectToLayer(4, delSave3);

	addNewObjectToLayer(4, stopBtn);
}

/// @brief 
/// Loads the text shown in the savescreen
void SaveScreen::loadText()
{
	int textIDCount = 2;
	for (int i = 0; i < 3; i++)
	{
		string name = "Empty";
		if (!savegame->isSaveGameDataEmpty(i + 1))
		{
			name = savegame->getSaveGameData(i + 1).saveGameName;

			string text = "Progress: " + to_string(savegame->getSaveGameData(i + 1).getOverWorldProgress()) + " %";
			auto* text2 = new Text(textIDCount++, new ColoredText(text, Color(0, 0, 0)), 120, 30, 520 + (float)(i * SPACING_INCREMENT), 425);
			addNewObjectToLayer(5, text2, false, true);

			text = "Achievements: " + to_string(savegame->getSaveGameData(i + 1).achievements.size());
			text2 = new Text(textIDCount++, new ColoredText(text, Color(0, 0, 0)), 120, 30, 520 + (float)(i * SPACING_INCREMENT), 460);
			addNewObjectToLayer(5, text2, false, true);

			text = "Last played: " + savegame->getSaveGameData(i + 1).getReadableTimeStamp();
			text2 = new Text(textIDCount++, new ColoredText(text, Color(0, 0, 0)), 200, 30, 480 + (float)(i * SPACING_INCREMENT), 500);
			addNewObjectToLayer(5, text2, false, true);

			text = "Totalscore: " + to_string(savegame->getSaveGameData(i + 1).totalScore);
			text2 = new Text(textIDCount++, new ColoredText(text, Color(0, 0, 0)), 120, 30, 520 + (float)(i * SPACING_INCREMENT), 540);
			addNewObjectToLayer(5, text2, false, true);

			text = "Total items: " + to_string(savegame->getSaveGameData(i + 1).characterData.inventory.items.size());
			text2 = new Text(textIDCount++, new ColoredText(text, Color(0, 0, 0)), 120, 30, 520 + (float)(i * SPACING_INCREMENT), 580);
			addNewObjectToLayer(5, text2, false, true);

		}
		auto* text1 = new Text(textIDCount++, new ColoredText(name, Color(0, 0, 0)), 100, 60, 520 + (float)(i* SPACING_INCREMENT), 380);
		addNewObjectToLayer(5, text1, false, true);
	}
}

/// @brief Called when Save 1 is clicked
void SaveScreen::onSave1BtnClick()
{
	savegame->setCurrentGameData(1);
	stateMachine.switchToScene("Overworld", true);
}

/// @brief Resets or creates a save file
/// @param id 
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

/// @brief Calls the create or delete save function
void SaveScreen::onSave1ExtraBtnClick()
{
	resetOrSaveSaveGame(1);
}

/// @brief Called when Save 2 is clicked
void SaveScreen::onSave2BtnClick()
{
	savegame->setCurrentGameData(2);
	stateMachine.switchToScene("Overworld", true);
}

/// @brief Calls the create or delete save function
void SaveScreen::onSave2ExtraBtnClick()
{
	resetOrSaveSaveGame(2);
}

/// @brief Called when Save 3 is clicked
void SaveScreen::onSave3BtnClick()
{
	savegame->setCurrentGameData(3);
	stateMachine.switchToScene("Overworld", true);
}

/// @brief Calls the create or delete save function
void SaveScreen::onSave3ExtraBtnClick()
{
	resetOrSaveSaveGame(3);
}

/// @brief Called when Back Button is clicked
void SaveScreen::onStopBtnClick() {
	stateMachine.switchToScene("MainMenu",false);
}