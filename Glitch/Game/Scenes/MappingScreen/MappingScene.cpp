#include "pch.h"
#include "MappingScene.h"
#include "Game/Game.h"

void MappingScene::onAttach()
{
	loadButtons();
	loadBackground();
	loadMusic();
}

void MappingScene::onDetach()
{
	Scene::onDetach();
}

void MappingScene::start(bool playSound)
{
}

void MappingScene::onUpdate(float deltaTime)
{
	if (moveToNextScene)
	{
		stateMachine->switchToScene(nextScene, useTransition, playSound);
	}
}

void MappingScene::loadBackground()
{
	shared_ptr<SpriteObject> BG_LAYER_0 = shared_ptr<SpriteObject>(new SpriteObject(-999, 1080, 1920, 1, 300, "Assets/Backgrounds/menu_Layer_0.png"));

	shared_ptr<Drawable> background = shared_ptr<Drawable>(new Drawable(-992));
	background->setStatic(true);
	background->setPositionX(0);
	background->setPositionY(1080);
	background->setWidth(1920);
	background->setHeight(1080);
	background->registerSprite(SpriteState::DEFAULT, BG_LAYER_0);
	background->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, background, false, true);
}

void MappingScene::loadMusic()
{
	engine->loadSound("MENU_SOUND", "Assets/Sound/file_example_WAV_1MG.wav");
}

void MappingScene::loadButtons()
{
	auto playerCommandsMap = invoker->getPlayerCommands();
	auto globalCommandsMap = invoker->getGlobalCommands();

	parseKeycodeList(invoker->getPlayerCommands(), "Player controls");
	
	listStartX = 850;
	listStartY = 400;

	parseKeycodeList(invoker->getGlobalCommands(), "Misc and global commands");

	listStartX = 200;
	listStartY = 500;
	createButtons();


	shared_ptr<SecondaryButton> stopBtn = shared_ptr<SecondaryButton>(new SecondaryButton(-993, "To Main Menu", onStopBtnClick, this->dispatcher));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(4, stopBtn);
}

void MappingScene::loadSaveGame()
{
}

/// @brief Function that creates text functions from the set keycode's
/// @param parseList 
/// @param header 
void MappingScene::parseKeycodeList(unordered_map<KeyCode, string> parseList, const string& header) {
	shared_ptr<SpriteObject> backgroundSprite = shared_ptr<SpriteObject>(new SpriteObject(-5656, 300, 500, 1, 1, "Assets/Sprites/PopUp/PopUpText-300x500.png"));
	shared_ptr<Drawable> backgroundBlock = shared_ptr<Drawable>(new Drawable(textId--));

	backgroundBlock->setHeight((((float)parseList.size() + 1) * 50) + 60);
	backgroundBlock->setWidth(((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP)* (header.length()) + 50);
	backgroundBlock->setPositionX(listStartX - 20);
	backgroundBlock->setPositionY(listStartY + (((float)parseList.size() + 1) * 50) + 20);

	backgroundBlock->registerSprite(SpriteState::DEFAULT, backgroundSprite);
	backgroundBlock->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(3, backgroundBlock);

	// set the header for the section
	shared_ptr<Text> text = shared_ptr<Text>(
		new Text(textId--,
			new ColoredText(header,
				Color(130, 41, 18),
				false
			),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * header.length(), 70.f, listStartX, (listStartY += 50.f))
		);
	addNewObjectToLayer(4, text);

	// parse and add the keycodes to the screen
	for (pair<KeyCode, string> command : parseList)
	{
		
		const string& identifier = command.second;
		// TODO make this a description (prob in json as attribute?) for now this works
		shared_ptr<Text> description = shared_ptr<Text>(new Text(textId--,
			new ColoredText(identifier,
				Color(0, 0, 0),
				false
			),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * identifier.length(), 50.f, listStartX + 80, listStartY += 50));

		
		addNewObjectToLayer(4, description);
	};
}

void MappingScene::createButtons() {
	shared_ptr<PrimaryButton> godModeBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onStopBtnClick, this->dispatcher));
	godModeBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	godModeBtn->setHeight(45);
	godModeBtn->setPositionX(listStartX);
	godModeBtn->setPositionY(listStartY);

	shared_ptr<Text> godModeString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("godmode"))],
			Color(0, 0, 0),
			false
		),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, godModeBtn);
	addNewObjectToLayer(5, godModeString);

	shared_ptr<PrimaryButton> jumpBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onJumpBtnClick, this->dispatcher));
	jumpBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	jumpBtn->setHeight(45);
	jumpBtn->setPositionX(listStartX);
	jumpBtn->setPositionY(listStartY += 50);

	shared_ptr<Text> jumpString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("jump"))],
			Color(0, 0, 0),
			false
		),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, jumpBtn);
	addNewObjectToLayer(5, jumpString);

	shared_ptr<PrimaryButton> leftBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onMoveLeftBtnClick, this->dispatcher));
	leftBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	leftBtn->setHeight(45);
	leftBtn->setPositionX(listStartX);
	leftBtn->setPositionY(listStartY += 50);

	shared_ptr<Text> moveLeftString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("moveLeft"))],
			Color(0, 0, 0),
			false
		),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, leftBtn);
	addNewObjectToLayer(5, moveLeftString);

	shared_ptr<PrimaryButton> rightBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onMoveRightBtnClick, this->dispatcher));
	rightBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	rightBtn->setHeight(45);
	rightBtn->setPositionX(listStartX);
	rightBtn->setPositionY(listStartY += 50);

	shared_ptr<Text> moveRightString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("moveRight"))],
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, rightBtn);
	addNewObjectToLayer(5, moveRightString);

	listStartX = 850;
	listStartY = 500;

	shared_ptr<PrimaryButton> inventoryBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onInventoryBtnClick, this->dispatcher));
	inventoryBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	inventoryBtn->setHeight(45);
	inventoryBtn->setPositionX(listStartX);
	inventoryBtn->setPositionY(listStartY);

	shared_ptr<Text> inventoryString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("inventory"))],
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, inventoryBtn);
	addNewObjectToLayer(5, inventoryString);

	shared_ptr<PrimaryButton> pauseBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onPauseBtnClick, this->dispatcher));
	pauseBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	pauseBtn->setHeight(45);
	pauseBtn->setPositionX(listStartX);
	pauseBtn->setPositionY(listStartY += 50);

	shared_ptr<Text> pauseString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("pause"))],
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, pauseBtn);
	addNewObjectToLayer(5, pauseString);
}