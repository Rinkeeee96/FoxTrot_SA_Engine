#include "pch.h"
#include "GameInfo.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"
#include "Game/General/GeneralGameDefines.h"


void GameInfo::onAttach()
{
	loadButtons();
	loadText();
	loadBackground();
}

/// @brief 
/// Create all text for this scene
void GameInfo::loadText() {

	shared_ptr<Text> header = shared_ptr<Text>(new Text(-564573, new ColoredText("Game info", Color(0, 0, 0), false),
		300, 100, WINDOW_WIDTH_CENTER - 100, 150));

	header->setDrawStatic(true);
	addNewObjectToLayer(4, header);
	
	this->text = splitText(
		"Controls \n\nThe controls can be changed in the mapping screen by pressing the buttons in front of the commands, the popups inventory, help and pause can be open and closed by pressing their binding. \n \nStory \n\nThe story is told by optional chapter markers on the map, you can click on them to read the story! \n \nGameplay \nPlay each level to the end and win by grabbing the present! \nif the game is too hard you can buy extra hearts in the shop, beware, their cost increases over time.. \n \nEnemies \n\nKill enemies by jumping on top of them! \n"
		, 1);

	for (size_t i = 0; i < this->text.size(); i++)
	{
		addNewObjectToLayer(4, this->text[i]);
	}
}
/// @brief 
/// Create all buttons for this scene
void GameInfo::loadButtons() {
	// Back button
	auto backBtn = shared_ptr<SecondaryButton>(new SecondaryButton(3, "To Main Menu", onBackClick, this->dispatcher));
	backBtn->setPositionX(WINDOW_WIDTH - 40 - backBtn->getWidth());
	backBtn->setPositionY(WINDOW_HEIGHT - 10 - backBtn->getHeight());

	addNewObjectToLayer(5, backBtn);
}

/// @brief 
/// Create the background for this scene
void GameInfo::loadBackground() {

	shared_ptr<SpriteObject>BG_IMAGE = shared_ptr<SpriteObject>(new SpriteObject(-1011, 1080, 1920, 1, 300, "Assets/Backgrounds/game_win_layer_0.png"));

	shared_ptr<Drawable> bgImage = shared_ptr<Drawable>(new Drawable(15));
	bgImage->setStatic(true);
	bgImage->setPositionX(0);
	bgImage->setPositionY(1080);
	bgImage->setWidth(1920);
	bgImage->setHeight(1080);
	bgImage->registerSprite(SpriteState::DEFAULT, BG_IMAGE);
	bgImage->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, bgImage, false, true);
}

/// @brief 
/// Create the sounds for this scene
void GameInfo::start(bool playSound)
{
}

/// @brief 
/// Splits lines based on line length without cutting words in half
/// @param String to split
/// @param The maximum length of line string
vector<string> GameInfo::splitToLines(string stringToSplit, int maximumLineLength)
{
	vector<string> ret;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = stringToSplit.find(delimiter)) != std::string::npos) {
		token = stringToSplit.substr(0, pos);

		if (ret.size() == 0) {
			ret.push_back(token + delimiter);
		}
		else {
			if (ret[ret.size() - 1].length() < maximumLineLength) {
				ret[ret.size() - 1] = ret[ret.size() - 1] + token + delimiter;
			}
			else {
				ret.push_back(token + delimiter);
			}
		}
		stringToSplit.erase(0, pos + delimiter.length());
	}
	return ret;
}

/// @brief 
/// Splits text on \n 
/// @param the text
vector<shared_ptr<Text>> GameInfo::splitText(string text, int startingId) {
	auto startingPos = 200;

	vector<shared_ptr<Text>> ret;
	std::string delimiter = "\n";

	size_t pos = 0;
	std::string token;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		token = text.substr(0, pos);

		auto result = splitToLines(token, NUMBER_OF_CHARACTERS_ON_LINE);
		for (size_t i = 0; i < result.size(); i++)
		{
			startingPos = startingPos + TEXT_HEIGHT;
			ret.push_back(shared_ptr<Text>(new Text(startingId++, new ColoredText(result[i], Color(0, 0, 0), false), ((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER) * result[i].length(), TEXT_HEIGHT, 25, (float)(startingPos))));
		}
		text.erase(0, pos + delimiter.length());
	}
	return ret;
}

void GameInfo::onUpdate(float deltaTime)
{
	if (moveToNextScene)
	{
		stateMachine->switchToScene(nextScene, useTransition, true);
	}

}

/// @brief 
/// Remove the sounds of the soundengine
void GameInfo::onDetach()
{
	Scene::onDetach();
}