#include "pch.h"
#include "SaveScreen.h"
#include "Game/Game.h"

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
	if(playSound)engine->startSound("MENU_SOUND");
}

/// @brief
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void SaveScreen::onUpdate(float deltaTime)
{
	if (moveToNextScene)
	{
		stateMachine->switchToScene(nextScene, useTransition, playSound);
	}
}

/// @brief 
/// Loads the background
void SaveScreen::loadBackground()
{
	shared_ptr<SpriteObject> BG_LAYER_0 = shared_ptr<SpriteObject>(new SpriteObject(-999, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png"));
	shared_ptr<SpriteObject> BG_LAYER_ADVENTRUE = shared_ptr<SpriteObject>(new SpriteObject(-998, 31, 33, 6, 300, "Assets/Sprites/Character/adventure_run_right.png"));
	shared_ptr<SpriteObject> BG_LAYER_2 = shared_ptr<SpriteObject>(new SpriteObject(-997, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_2.png"));
	shared_ptr<SpriteObject> emptyBlock = shared_ptr<SpriteObject>(new SpriteObject(-996, 309, 253, 1, 300, "Assets/Inventory/text_background.png"));

	shared_ptr<Drawable> layer0 = shared_ptr<Drawable>(new Drawable(-992));
	layer0->setStatic(true);
	layer0->setPositionX(0);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> block1 = shared_ptr<Drawable>(new Drawable(-991));
	block1->setStatic(true);
	block1->setPositionX(550);
	block1->setPositionY(825);
	block1->setWidth(300);
	block1->setHeight(500);
	block1->registerSprite(SpriteState::DEFAULT, emptyBlock);
	block1->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> block2 = shared_ptr<Drawable>(new Drawable(-990));
	block2->setStatic(true);
	block2->setPositionX(1050);
	block2->setPositionY(825);
	block2->setWidth(300);
	block2->setHeight(500);
	block2->registerSprite(SpriteState::DEFAULT, emptyBlock);
	block2->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> block3 = shared_ptr<Drawable>(new Drawable(-989));
	block3->setStatic(true);
	block3->setPositionX(1550);
	block3->setPositionY(825);
	block3->setWidth(300);
	block3->setHeight(500);
	block3->registerSprite(SpriteState::DEFAULT, emptyBlock);
	block3->changeToState(SpriteState::DEFAULT);

	shared_ptr<Drawable> animation = shared_ptr<Drawable>(new Drawable(-988));
	animation->setStatic(true);
	animation->setPositionX(175);
	animation->setPositionY(875);
	animation->setWidth(370);
	animation->setHeight(370);
	animation->registerSprite(SpriteState::DEFAULT, BG_LAYER_ADVENTRUE);
	animation->changeToState(SpriteState::DEFAULT);
	animation->setScalable(false);

	shared_ptr<Drawable> layer2 = shared_ptr<Drawable>(new Drawable(-987));
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
	engine->loadSound("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav");
}

/// @brief 
/// Loads all the buttons in the Overworld
void SaveScreen::loadButtons()
{
	string nameBtnExtra = "Create New";
	if (!savegame->isSaveGameDataEmpty(1))
	{
		shared_ptr<PrimaryButton>save1 = shared_ptr<PrimaryButton>(new PrimaryButton(-996, "Start!", onSave1BtnClick, this->dispatcher));
		save1->setPositionX(605);
		save1->setPositionY(750);
		addNewObjectToLayer(4, save1);
		nameBtnExtra = "Delete";
	}

	shared_ptr<PrimaryButton> delSave1 = shared_ptr<PrimaryButton>(new PrimaryButton(-992, nameBtnExtra, onSave1ExtraBtnClick, this->dispatcher));
	delSave1->setPositionX(605);
	delSave1->setPositionY(805);

	nameBtnExtra = "Create New";
	if (!savegame->isSaveGameDataEmpty(2))
	{
		shared_ptr<PrimaryButton> save1 = shared_ptr<PrimaryButton>(new PrimaryButton(-995, "Start!", onSave2BtnClick, this->dispatcher));
		save1->setPositionX(605 + SPACING_INCREMENT);
		save1->setPositionY(750);
		addNewObjectToLayer(4, save1);
		nameBtnExtra = "Delete";
	}

	shared_ptr<PrimaryButton> delSave2 = shared_ptr<PrimaryButton>(new PrimaryButton(-991, nameBtnExtra, onSave2ExtraBtnClick, this->dispatcher));
	delSave2->setPositionX(605 + SPACING_INCREMENT);
	delSave2->setPositionY(805);

	nameBtnExtra = "Create New";
	if (!savegame->isSaveGameDataEmpty(3))
	{
		shared_ptr<PrimaryButton> save1 = shared_ptr<PrimaryButton>(new PrimaryButton(-994, "Start!", onSave3BtnClick, this->dispatcher));
		save1->setPositionX(605 + SPACING_INCREMENT * 2);
		save1->setPositionY(750);
		addNewObjectToLayer(4, save1);
		nameBtnExtra = "Delete";
	}

	shared_ptr<PrimaryButton> delSave3 = shared_ptr<PrimaryButton>(new PrimaryButton(-990, nameBtnExtra, onSave3ExtraBtnClick, this->dispatcher));
	delSave3->setPositionX(605 + SPACING_INCREMENT * 2);
	delSave3->setPositionY(805);

	shared_ptr<SecondaryButton> stopBtn = shared_ptr<SecondaryButton>(new SecondaryButton(-993, "To Main Menu", onStopBtnClick, this->dispatcher));
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
			shared_ptr<Text> text2 = shared_ptr<Text>(new Text(textIDCount++, new ColoredText(text, Color(0, 0, 0)), 120, 30, 520 + (float)(i * SPACING_INCREMENT), 425));
			addNewObjectToLayer(5, text2, false, true);

			text = "Achievements: " + to_string(savegame->getSaveGameData(i + 1).achievements.size());
			text2 = shared_ptr<Text>(new Text(textIDCount++, new ColoredText(text, Color(0, 0, 0)), 120, 30, 520 + (float)(i * SPACING_INCREMENT), 460));
			addNewObjectToLayer(5, text2, false, true);

			text = "Last played: " + savegame->getSaveGameData(i + 1).getReadableTimeStamp();
			text2 = shared_ptr<Text>(new Text(textIDCount++, new ColoredText(text, Color(0, 0, 0)), 200, 30, 480 + (float)(i * SPACING_INCREMENT), 500));
			addNewObjectToLayer(5, text2, false, true);

			text = "Totalscore: " + to_string(savegame->getSaveGameData(i + 1).totalScore);
			text2 = shared_ptr<Text>(new Text(textIDCount++, new ColoredText(text, Color(0, 0, 0)), 120, 30, 520 + (float)(i * SPACING_INCREMENT), 540));
			addNewObjectToLayer(5, text2, false, true);
		}
		shared_ptr<Text> text1 = shared_ptr<Text>(new Text(textIDCount++, new ColoredText(name, Color(0, 0, 0)), 100, 60, 520 + (float)(i* SPACING_INCREMENT), 380));
		addNewObjectToLayer(5, text1, false, true);
	}
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
		stateMachine->switchToScene("SaveScreen", false, false);
	}
	else
	{
		savegame->deleteSaveGameData(id);
		stateMachine->switchToScene("SaveScreen", false, false);
	}
}
