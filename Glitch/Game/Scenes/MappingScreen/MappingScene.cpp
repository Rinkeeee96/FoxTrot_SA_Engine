#include "pch.h"
#include "MappingScene.h"
#include "Game/Game.h"
#include "Game/General/KeyCodeStringMap.h"

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

	
	string remap = "Press a button and then a key to remap it.";
	shared_ptr<Text> text = shared_ptr<Text>(new Text(textId--,
		new ColoredText(remap,
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * remap.length(), 50.f, 175, 350));
	addNewObjectToLayer(1, text, false, true);
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


	shared_ptr<SecondaryButton> stopBtn = shared_ptr<SecondaryButton>(new SecondaryButton(-9993, "To Main Menu", onStopBtnClick, this->dispatcher));
	stopBtn->setPositionX(WINDOW_WIDTH - 40 - stopBtn->getWidth());
	stopBtn->setPositionY(WINDOW_HEIGHT - 10 - stopBtn->getHeight());

	addNewObjectToLayer(3, stopBtn);
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
}

void MappingScene::createButtons() {
	shared_ptr<PrimaryButton> godModeBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onGodModeBtnClick, this->dispatcher));
	godModeBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	godModeBtn->setHeight(45);
	godModeBtn->setPositionX(listStartX);
	godModeBtn->setPositionY(listStartY);

	shared_ptr<Text> godModeIdentifierString = shared_ptr<Text>(new Text(textId--,
		new ColoredText("God mode",
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * string("God mode").length(), 50.f, listStartX + 80, listStartY));

	shared_ptr<Text> godModeString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("godmode"))],
			Color(0, 0, 0),
			false
		),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, godModeIdentifierString);
	addNewObjectToLayer(4, godModeBtn);
	addNewObjectToLayer(5, godModeString);

	shared_ptr<PrimaryButton> jumpBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onJumpBtnClick, this->dispatcher));
	jumpBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	jumpBtn->setHeight(45);
	jumpBtn->setPositionX(listStartX);
	jumpBtn->setPositionY(listStartY += 50);

	shared_ptr<Text> jumpIdentifierString = shared_ptr<Text>(new Text(textId--,
		new ColoredText("Jump",
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * string("Jump").length(), 50.f, listStartX + 80, listStartY));

	shared_ptr<Text> jumpString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("jump"))],
			Color(0, 0, 0),
			false
		),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, jumpIdentifierString);
	addNewObjectToLayer(4, jumpBtn);
	addNewObjectToLayer(5, jumpString);

	shared_ptr<PrimaryButton> leftBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onMoveLeftBtnClick, this->dispatcher));
	leftBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	leftBtn->setHeight(45);
	leftBtn->setPositionX(listStartX);
	leftBtn->setPositionY(listStartY += 50);

	shared_ptr<Text> leftIdentifierString = shared_ptr<Text>(new Text(textId--,
		new ColoredText("Move left",
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * string("Move left").length(), 50.f, listStartX + 80, listStartY));

	shared_ptr<Text> moveLeftString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("moveLeft"))],
			Color(0, 0, 0),
			false
		),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, leftIdentifierString);
	addNewObjectToLayer(4, leftBtn);
	addNewObjectToLayer(5, moveLeftString);

	shared_ptr<PrimaryButton> rightBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onMoveRightBtnClick, this->dispatcher));
	rightBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	rightBtn->setHeight(45);
	rightBtn->setPositionX(listStartX);
	rightBtn->setPositionY(listStartY += 50);

	shared_ptr<Text> rightIdentifierString = shared_ptr<Text>(new Text(textId--,
		new ColoredText("Move right",
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * string("Move right").length(), 50.f, listStartX + 80, listStartY));

	shared_ptr<Text> moveRightString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("moveRight"))],
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, rightIdentifierString);
	addNewObjectToLayer(4, rightBtn);
	addNewObjectToLayer(5, moveRightString);

	listStartX = 850;
	listStartY = 500;

	shared_ptr<PrimaryButton> inventoryBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onInventoryBtnClick, this->dispatcher));
	inventoryBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	inventoryBtn->setHeight(45);
	inventoryBtn->setPositionX(listStartX);
	inventoryBtn->setPositionY(listStartY);

	shared_ptr<Text> inventoryIdentifierString = shared_ptr<Text>(new Text(textId--,
		new ColoredText("Inventory",
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * string("Inventory").length(), 50.f, listStartX + 80, listStartY));

	shared_ptr<Text> inventoryString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("inventory"))],
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	addNewObjectToLayer(4, inventoryIdentifierString);
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

	shared_ptr<Text> pauseIdentifierString = shared_ptr<Text>(new Text(textId--,
		new ColoredText("Pause game",
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * string("Pause game").length(), 50.f, listStartX + 80, listStartY));

	addNewObjectToLayer(4, pauseIdentifierString);
	addNewObjectToLayer(4, pauseBtn);
	addNewObjectToLayer(5, pauseString);

	shared_ptr<PrimaryButton> helpBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onHelpBtnClick, this->dispatcher));
	helpBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	helpBtn->setHeight(45);
	helpBtn->setPositionX(listStartX);
	helpBtn->setPositionY(listStartY += 50);

	shared_ptr<Text> helpString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("help"))],
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	shared_ptr<Text> helpIdentifierString = shared_ptr<Text>(new Text(textId--,
		new ColoredText("Help screen",
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * string("Help screen").length(), 50.f, listStartX + 80, listStartY));

	addNewObjectToLayer(4, helpIdentifierString);
	addNewObjectToLayer(4, helpBtn);
	addNewObjectToLayer(5, helpString);

	shared_ptr<PrimaryButton> slowerBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onSlowerBtnClick, this->dispatcher));
	slowerBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	slowerBtn->setHeight(45);
	slowerBtn->setPositionX(listStartX);
	slowerBtn->setPositionY(listStartY += 50);

	shared_ptr<Text> slowerString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("slower"))],
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	shared_ptr<Text> slowerIdentifierString = shared_ptr<Text>(new Text(textId--,
		new ColoredText("Slower game speed",
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * string("Slower game speed").length(), 50.f, listStartX + 80, listStartY));

	addNewObjectToLayer(4, slowerIdentifierString);
	addNewObjectToLayer(4, slowerBtn);
	addNewObjectToLayer(5, slowerString);

	shared_ptr<PrimaryButton> fasterBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onFasterBtnClick, this->dispatcher));
	fasterBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1) + 25);
	fasterBtn->setHeight(45);
	fasterBtn->setPositionX(listStartX);
	fasterBtn->setPositionY(listStartY += 50);

	shared_ptr<Text> fasterString = shared_ptr<Text>(new Text(textId--,
		new ColoredText(keycodeStringMap[KeyCode(invoker->getKeycodeFromIdentifier("faster"))],
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));

	shared_ptr<Text> fasterIdentifierString = shared_ptr<Text>(new Text(textId--,
		new ColoredText("Faster game speed",
			Color(0, 0, 0),
			false
		),
		((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * string("Faster game speed").length(), 50.f, listStartX + 80, listStartY));

	addNewObjectToLayer(4, fasterIdentifierString);
	addNewObjectToLayer(4, fasterBtn);
	addNewObjectToLayer(5, fasterString);
}

void MappingScene::updatePlayerCommand(const string& identifier)
{
	// Get new keycode
	KeyCode keyCode = engine->getSingleKeyStroke();

	// Set new keycode in map
	invoker->updatePlayerCommand(keyCode, identifier);
	// save the json file
	builder.saveKeybindings(invoker);

	listStartX = 200;
	listStartY = 400;
	removeLayer(3);
	removeLayer(4);
	removeLayer(5);

	loadButtons();
}

void MappingScene::updateGlobalCommand(const string& identifier)
{
	// Get new keycode
	KeyCode keyCode = engine->getSingleKeyStroke();

	// Set new keycode in map
	invoker->updateGlobalCommand(keyCode, identifier);
	// save the json file
	builder.saveKeybindings(invoker);

	listStartX = 200;
	listStartY = 400;
	removeLayer(3);
	removeLayer(4);
	removeLayer(5);

	loadButtons();
}
