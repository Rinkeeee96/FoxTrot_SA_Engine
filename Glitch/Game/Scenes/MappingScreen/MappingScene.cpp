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
	auto invoker = (GameKeypressInvoker*)engine->getKeypressedInvoker();
	auto playerCommandsMap = invoker->getPlayerCommands();
	auto globalCommandsMap = invoker->getGlobalCommands();

	parseKeycodeList(invoker->getPlayerCommands(), "player controls");
	
	listStartX = 850;
	listStartY = 400;

	parseKeycodeList(invoker->getGlobalCommands(), "misc and global commands");



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
		const KeyCode& keyCode = command.first;
		const string& identifier = command.second;

		shared_ptr<PrimaryButton> keycodeBtn = shared_ptr<PrimaryButton>(new PrimaryButton(textId--, "", onStopBtnClick, this->dispatcher));
		keycodeBtn->setWidth((((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1)+25);
		keycodeBtn->setHeight(45);
		keycodeBtn->setPositionX(listStartX);
		keycodeBtn->setPositionY(listStartY += 50.f);

		shared_ptr<Text> keycodeString = shared_ptr<Text>(new Text(textId--,
			new ColoredText(keycodeStringMap[keyCode],
				Color(0, 0, 0),
				false
			),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * 1, 50.f, listStartX + 10, listStartY));
		// TODO make this a description (prob in json as attribute?) for now this works
		shared_ptr<Text> description = shared_ptr<Text>(new Text(textId--,
			new ColoredText(identifier,
				Color(0, 0, 0),
				false
			),
			((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER_HELP) * identifier.length(), 50.f, listStartX + 100, listStartY)
			);

		addNewObjectToLayer(4, keycodeBtn);
		addNewObjectToLayer(5, keycodeString);
		addNewObjectToLayer(4, description);
	};
}