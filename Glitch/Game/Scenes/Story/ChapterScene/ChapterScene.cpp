#include "pch.h"
#include "ChapterScene.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

ChapterScene::ChapterScene(const int id, Engine& _engine, SceneStateMachine& _statemachine) : GameScene(id, _engine, _statemachine)
{
	dispatcher.setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(ChapterScene::onKeyPressed));
}

/// @brief 
/// Handles key pressed, moves the text faster or slower based on KeyPressed
bool ChapterScene::onKeyPressed(const Event& event)
{
	auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);

	switch (keyPressedEvent.getKeyCode())
	{
	case KeyCode::KEY_LEFT:
		this->speed_ -= 1;
		break;
	case KeyCode::KEY_RIGHT:
		this->speed_ += 1;
		break;
	default:
		return false;
	}
	return false;
}

/// @brief 
/// Splits lines based on line length without cutting words in half
/// @param String to split
/// @param The maximum length of line string
vector<string> ChapterScene::splitToLines(string stringToSplit, int maximumLineLength)
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
vector<Text*> ChapterScene::splitText(string text, int startingId) {
	auto startingPos = START_Y_POS;

	vector<Text*> ret;
	std::string delimiter = "\n";

	size_t pos = 0;
	std::string token;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		token = text.substr(0, pos);

		auto result = splitToLines(token, NUMBER_OF_CHARACTERS_ON_LINE);
		for (size_t i = 0; i < result.size(); i++)
		{
			startingPos = startingPos + TEXT_HEIGHT;
			ret.push_back(new Text(startingId++, new ColoredText(result[i], Color(255, 255, 255), false), ((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER) * result[i].length(), TEXT_HEIGHT, 25, (float)(WINDOW_HEIGHT + startingPos)));
		}
		text.erase(0, pos + delimiter.length());
	}
	return ret;
}

/// @brief 
/// Create all buttons for this scene
void ChapterScene::loadButtons() {
	// Back button
	auto* backBtn = new SecondaryButton(3, "Skip", std::bind(&ChapterScene::onSkipClick, *this), this->dispatcher);
	backBtn->setPositionX(WINDOW_WIDTH - 40 - backBtn->getWidth());
	backBtn->setPositionY(WINDOW_HEIGHT - 10 - backBtn->getHeight());

	addNewObjectToLayer(4, backBtn);
}

/// @brief 
/// Creates text to parse from .txt
void ChapterScene::setTextFromFile(string path, int startingId) {
	auto stream = fileLoader.readFile(path);
	string appendString;
	string currentString;
	while (getline(stream, currentString)) {
		appendString = appendString + currentString + "\n";
	}
	stream.close();
	this->text = splitText(appendString, startingId);
}

/// @brief 
/// Moves text in screen by speed
void ChapterScene::onUpdate()
{
	for (size_t i = 0; i < this->text.size(); i++)
	{
		this->text[i]->setPositionY(this->text[i]->getPositionY() - speed_);
		if (text[this->text.size() - 1]->getPositionY() < 0) stateMachine.switchToScene("Overworld", false);
	}
}

/// @brief 
/// A callback function for overworldBTN
/// Start transition scene to overworl
void ChapterScene::onSkipClick() {
	stateMachine.switchToScene("Overworld", false);
}
