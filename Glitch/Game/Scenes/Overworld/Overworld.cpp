#include "pch.h"
#include "Overworld.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

/// @brief 
/// Loadbuttons
/// LoadBackground
/// LoadMusic
void Overworld::onAttach()
{
	
	loadButtons();
	loadBackground();
	loadMusic();
	loadSaveGame();
	loadAchievements();
}

/// @brief 
/// Loads all the buttons in the Overworld
void Overworld::loadButtons() {
	shared_ptr<SpriteObject> defaultBtnSprite = shared_ptr<SpriteObject>(new SpriteObject(101013, 11, 15, 1, 300, "Assets/Buttons/village_orange.png"));
	shared_ptr<SpriteObject> hoverBtnSprite = shared_ptr<SpriteObject>(new SpriteObject(101012, 11, 15, 1, 300, "Assets/Buttons/village_gray.png"));

	shared_ptr<SpriteObject> bookBtnSprite = shared_ptr<SpriteObject>(new SpriteObject(101014, 300, 300, 1, 300, "Assets/Buttons/book.png"));
	shared_ptr<SpriteObject> bookHoverBtnSprite = shared_ptr<SpriteObject>(new SpriteObject(101015, 300, 300, 1, 300, "Assets/Buttons/book_hoover.png"));

	shared_ptr<Button> shop = shared_ptr<Button>(new Button(10, ColoredText("", Color(255, 255, 255)), onShopBtnClick, defaultBtnSprite, this->dispatcher));
	shop->setWidth(32);
	shop->setHeight(32);
	shop->setPositionX(480);
	shop->setPositionY(840);
	shop->registerHoverSprite(hoverBtnSprite);

	shared_ptr<Text> shopText = shared_ptr<Text>(new Text(15, new ColoredText("Shop", Color(0, 0, 0)), 70, 50, 565, 850));

	shared_ptr<Button> shop1 = shared_ptr<Button>(new Button(11, ColoredText("", Color(255, 255, 255)), onShopBtnClick, defaultBtnSprite, this->dispatcher));
	shop1->setWidth(32);
	shop1->setHeight(32);
	shop1->setPositionX(600);
	shop1->setPositionY(830);
	shop1->registerHoverSprite(hoverBtnSprite);

	shared_ptr<Button> shop2 = shared_ptr<Button>(new Button(12, ColoredText("", Color(255, 255, 255)), onShopBtnClick, defaultBtnSprite, this->dispatcher));
	shop2->setWidth(32);
	shop2->setHeight(32);
	shop2->setPositionX(535);
	shop2->setPositionY(870);
	shop2->registerHoverSprite(hoverBtnSprite);

	shared_ptr<Button> level1Btn = shared_ptr<Button>(new Button(1, ColoredText("", Color(255, 255, 255)), onLevel1BtnClick, defaultBtnSprite, this->dispatcher));
	level1Btn->setWidth(32);
	level1Btn->setHeight(32);
	level1Btn->setPositionX(713);
	level1Btn->setPositionY(355);
	level1Btn->registerHoverSprite(hoverBtnSprite);

	shared_ptr<Text> level1TextBtn = shared_ptr<Text>(new Text(2, new ColoredText("Level 1, Score: " + to_string(savegame->getCurrentGameData().levelData[0].score), Color(0, 0, 0)), 120, 30, 613, 350 + 20));

	shared_ptr<Button> level2Btn = shared_ptr<Button>(new Button(3, ColoredText("", Color(255, 255, 255)), onLevel2BtnClick, defaultBtnSprite, this->dispatcher));
	level2Btn->setWidth(32);
	level2Btn->setHeight(32);
	level2Btn->setPositionX(743);
	level2Btn->setPositionY(640);
	level2Btn->registerHoverSprite(hoverBtnSprite);

	string level2Name = "Locked";
	if (savegame->getCurrentGameData().levelData[1].completed)
	{
		level2Name = "Level 2, Score: " + to_string(savegame->getCurrentGameData().levelData[1].score);
	}
	shared_ptr<Text> level2TextBtn = shared_ptr<Text>(new Text(4, new ColoredText(level2Name, Color(0, 0, 0)), 120, 30, 648, 640 + 20));

	if (!savegame->getCurrentGameData().levelData[1].completed)
	{
		level2Btn->disable();
	}

	string level3Name = "Locked";
	if (savegame->getCurrentGameData().levelData[2].completed)
	{
		level3Name = "Level 3, Score: " + to_string(savegame->getCurrentGameData().levelData[2].score);
	}
	shared_ptr<Button> level3Btn = shared_ptr<Button>(new Button(5, ColoredText("", Color(255, 255, 255)), onLevel3BtnClick, defaultBtnSprite, this->dispatcher));
	level3Btn->setWidth(32);
	level3Btn->setHeight(32);
	level3Btn->setPositionX(1000);
	level3Btn->setPositionY(667);
	level3Btn->registerHoverSprite(hoverBtnSprite);

	shared_ptr<Text> level3TextBtn = shared_ptr<Text>(new Text(6, new ColoredText(level3Name, Color(0, 0, 0)), 120, 30, 900, 667 + 15));
	if (!savegame->getCurrentGameData().levelData[2].completed)
	{
		level3Btn->disable();
	}

	string level4Name = "Locked";
	if (savegame->getCurrentGameData().levelData[3].completed)
	{
		level4Name = "Level 4, Score: " + to_string(savegame->getCurrentGameData().levelData[3].score);
	}
	shared_ptr<Button> level4Btn = shared_ptr<Button>(new Button(7, ColoredText("", Color(255, 255, 255)), onLevel4BtnClick, defaultBtnSprite, this->dispatcher));
	level4Btn->setWidth(32);
	level4Btn->setHeight(32);
	level4Btn->setPositionX(1495);
	level4Btn->setPositionY(638);
	level4Btn->registerHoverSprite(hoverBtnSprite);

	shared_ptr<Text> level4TextBtn = shared_ptr<Text>(new Text(8, new ColoredText(level4Name, Color(0, 0, 0)), 120, 30, 1315, 638 - 50));
	if (!savegame->getCurrentGameData().levelData[3].completed)
	{
		level4Btn->disable();
	}

	shared_ptr<SecondaryButton> stopBtn = shared_ptr<SecondaryButton>(new SecondaryButton(9, "To Main Menu", onStopBtnClick, this->dispatcher));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	shared_ptr<Button> chapterOne = shared_ptr<Button>(new Button(55, ColoredText("", Color(0, 0, 0)), onChapterOneClick, bookBtnSprite, this->dispatcher));
	chapterOne->setWidth(32);
	chapterOne->setHeight(32);
	chapterOne->setPositionX(287);
	chapterOne->setPositionY(452);
	chapterOne->registerHoverSprite(bookHoverBtnSprite);

	shared_ptr<Text> chapterOneTxt = shared_ptr<Text>(new Text(56, new ColoredText("Chapter one", Color(0, 0, 0), false), 100, 50, 287 - 35, 452 + 40));



	shared_ptr<Button> chapterTwo = shared_ptr<Button>(new Button(76, ColoredText("", Color(0, 0, 0)), onChapterTwoClick, bookBtnSprite, this->dispatcher));
	chapterTwo->setWidth(32);
	chapterTwo->setHeight(32);
	chapterTwo->setPositionX(1265);
	chapterTwo->setPositionY(675);
	chapterTwo->registerHoverSprite(bookHoverBtnSprite);
	if (!savegame->getCurrentGameData().levelData[3].completed)
	{
		chapterTwo->disable();
	}

	shared_ptr<Text> chapterTwoTxt = shared_ptr<Text>(new Text(77, new ColoredText("Chapter two", Color(0, 0, 0), false), 100, 50, 1270 - 35, 675 + 35));

	shared_ptr<Button> chapterThree = shared_ptr<Button>(new Button(78, ColoredText("", Color(0, 0, 0)), onChapterThreeClick, bookBtnSprite, this->dispatcher));
	chapterThree->setWidth(32);
	chapterThree->setHeight(32);
	chapterThree->setPositionX(1760);
	chapterThree->setPositionY(225);
	chapterThree->registerHoverSprite(bookHoverBtnSprite);

	shared_ptr<Text> chapterThreeTxt = shared_ptr<Text>(new Text(79, new ColoredText("Chapter three", Color(0, 0, 0), false), 100, 50, 1760 - 35, 225 + 35));
	if (!savegame->getCurrentGameData().levelData[5].completed)
	{
		chapterThree->disable();
	}

	string level5Name = "Locked";
	if (savegame->getCurrentGameData().levelData[4].completed)
	{
		level5Name = "Level 5, Score: " + to_string(savegame->getCurrentGameData().levelData[4].score);
	}
	shared_ptr<Button> level5Btn = shared_ptr<Button>(new Button(23, ColoredText("", Color(255, 255, 255)), onLevel5BtnClick, defaultBtnSprite, this->dispatcher));
	level5Btn->setWidth(32);
	level5Btn->setHeight(32);
	level5Btn->setPositionX(1465);
	level5Btn->setPositionY(250);
	level5Btn->registerHoverSprite(hoverBtnSprite);
	shared_ptr<Text> level5TextBtn = shared_ptr<Text>(new Text(24, new ColoredText(level5Name, Color(0, 0, 0)), 120, 30, 1360, 250 + 20));
	if (!savegame->getCurrentGameData().levelData[4].completed)
	{
		level5Btn->disable();
	}

	addNewObjectToLayer(3, chapterOne);
	addNewObjectToLayer(3, chapterOneTxt);
	addNewObjectToLayer(3, chapterTwo);
	addNewObjectToLayer(3, chapterTwoTxt);
	addNewObjectToLayer(3, chapterThree);
	addNewObjectToLayer(3, chapterThreeTxt);
	addNewObjectToLayer(3, level1Btn);
	addNewObjectToLayer(3, level1TextBtn);
	addNewObjectToLayer(3, level2Btn);
	addNewObjectToLayer(3, level2TextBtn);
	addNewObjectToLayer(3, level3Btn);
	addNewObjectToLayer(3, level3TextBtn);
	addNewObjectToLayer(3, level4Btn);
	addNewObjectToLayer(3, level4TextBtn);
	addNewObjectToLayer(3, level5Btn);
	addNewObjectToLayer(3, level5TextBtn);
	addNewObjectToLayer(3, stopBtn);
	addNewObjectToLayer(3, shop);
	addNewObjectToLayer(3, shopText);
	addNewObjectToLayer(3, shop1);
	addNewObjectToLayer(3, shop2);
}

/// @brief 
void Overworld::loadSaveGame()
{
	shared_ptr<SpriteObject> block_300x100 = shared_ptr<SpriteObject>(new SpriteObject(-2500, 100, 300, 1, 300, "Assets/Textblocks/block_300x100.png"));
	shared_ptr<SpriteObject> block_200x500 = shared_ptr<SpriteObject>(new SpriteObject(-2501, 500, 200, 1, 300, "Assets/Textblocks/block_200x500.png"));
	shared_ptr<SpriteObject> emptyBlock = shared_ptr<SpriteObject>(new SpriteObject(-2502, 309, 253, 1, 300, "Assets/Inventory/text_background.png"));

	shared_ptr<Drawable> block1 = shared_ptr<Drawable>(new Drawable(-2501));
	block1->setStatic(true);
	block1->setPositionX(1600);
	block1->setPositionY(120);
	block1->setWidth(300);
	block1->setHeight(100);
	block1->registerSprite(SpriteState::DEFAULT, block_300x100);
	block1->changeToState(SpriteState::DEFAULT);


	shared_ptr<Drawable> achievements = shared_ptr<Drawable>(new Drawable(-2502));
	achievements->setStatic(true);
	achievements->setPositionX(20);
	achievements->setPositionY(800);
	achievements->setWidth(200);
	achievements->setHeight(500);
	achievements->registerSprite(SpriteState::DEFAULT, block_200x500);
	achievements->changeToState(SpriteState::DEFAULT);

	int textIDCount = 100;

	shared_ptr<Text> text2 = shared_ptr<Text>(new Text(textIDCount++, new ColoredText(savegame->getCurrentGameData().saveGameName + " " + savegame->getCurrentGameData().getReadableTimeStamp(), Color(0, 0, 0)), 200, 30, 1550, 40));
	addNewObjectToLayer(5, text2, false, true);

	text2 = shared_ptr<Text>(new Text(textIDCount++, new ColoredText("Total score: " + to_string(savegame->getCurrentGameData().totalScore), Color(0, 0, 0)), 200, 30, 1550, 90));
	addNewObjectToLayer(5, text2, false, true);

	addNewObjectToLayer(4, block1, false, true);
	addNewObjectToLayer(4, achievements, false, true);
}

/// @brief 
void Overworld::loadAchievements()
{
	int textIDCount = 0;

	shared_ptr<Text> text2 = shared_ptr<Text>(new Text(textIDCount++, new ColoredText("Achievements", Color(0, 0, 0)), 120, 30, 8, 340));
	addNewObjectToLayer(5, text2, false, true);

	int linecount = 30;

	for (auto achievement : savegame->getCurrentGameData().achievements)
	{
		shared_ptr<Text> text2 = shared_ptr<Text>(new Text(textIDCount++, new ColoredText(achievement, Color(0, 0, 0)), 120, 30, 5, 340 + (float)linecount));
		addNewObjectToLayer(5, text2, false, true);

		linecount += 30;
	}
}

/// @brief 
/// Loads the background
void Overworld::loadBackground() {
	shared_ptr<SpriteObject> BG_LAYER_0 = shared_ptr<SpriteObject>(new SpriteObject(-9123, 1440, 1920, 1, 1, "Assets/Overworld/World.png"));

	shared_ptr<Drawable> layer0 = shared_ptr<Drawable>(new Drawable(1));
	layer0->setStatic(true);
	layer0->setPositionX(0);
	layer0->setPositionY(1080);
	layer0->setWidth(1920);
	layer0->setHeight(1080);
	layer0->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	layer0->changeToState(SpriteState::DEFAULT);
	layer0->setScalable(false);

	addNewObjectToLayer(1, layer0, false, true);
}

/// @brief 
/// Load the sounds for this scene
void Overworld::loadMusic() {
	engine->loadSound("OVER_WORLD", "Assets/Sound/file_example_WAV_1MG.wav");
}

/// @brief 
/// Create the sounds for this scene
void Overworld::start(bool playSound)
{
	if(playSound)engine->startSound("OVER_WORLD");
}

/// @brief 
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void Overworld::onUpdate(float deltaTime)
{
	if (moveToNextScene)
	{
		stateMachine->switchToScene(nextScene, useTransition, playSound);
	}
}

/// @brief 
/// Remove the sounds of the soundengine
void Overworld::onDetach()
{
	Scene::onDetach();
}
