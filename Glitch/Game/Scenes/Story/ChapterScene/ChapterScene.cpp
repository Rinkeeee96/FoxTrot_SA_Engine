#include "pch.h"
#include "ChapterScene.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"
#include "Game/General/KeyCodeStringMap.h"

ChapterScene::ChapterScene(const int id, unique_ptr<Engine>& _engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, _engine, _statemachine)
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
	case KeyCode::KEY_DOWN:
		this->speed_ = 0;
		break; 
	case KeyCode::KEY_LEFT:
		if (this->speed_ == MAX_SPEED * -1) break;
		this->speed_ -= TEXT_SPEED_INCREMENT;
		break;
	case KeyCode::KEY_RIGHT:
		if (this->speed_ == MAX_SPEED) break;
		this->speed_ += TEXT_SPEED_INCREMENT;
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
vector<shared_ptr<Text>> ChapterScene::splitText(string text, int startingId) {
	auto startingPos = START_Y_POS;

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
			ret.push_back(shared_ptr<Text>(new Text(startingId++, new ColoredText(result[i], Color(255, 255, 255), false), ((float)WINDOW_WIDTH / TEXT_SIZE_DIVIDER) * result[i].length(), TEXT_HEIGHT, 25, (float)(WINDOW_HEIGHT + startingPos))));
		}
		text.erase(0, pos + delimiter.length());
	}
	return ret;
}

/// @brief 
/// Create all buttons for this scene
void ChapterScene::loadButtons() {
	shared_ptr<Text> help = shared_ptr<Text>(new Text(-5645585, new ColoredText("Arrow key controls for text speed:", Color(255, 255, 255), false),
		550, 50, WINDOW_WIDTH - 900, WINDOW_HEIGHT - 80));
	shared_ptr<Text> text = shared_ptr<Text>(new Text(-564573, new ColoredText(keycodeStringMap[KeyCode::KEY_DOWN] + " = stop : " + keycodeStringMap[KeyCode::KEY_LEFT] + " = slower : " + keycodeStringMap[KeyCode::KEY_RIGHT] + " = faster", Color(255, 255, 255), false),
		550, 50, WINDOW_WIDTH - 900, WINDOW_HEIGHT - 30));
	addNewObjectToLayer(5, text);
	addNewObjectToLayer(5, help);
	
	// Back button
	shared_ptr<SecondaryButton> backBtn = shared_ptr<SecondaryButton>(new SecondaryButton(3, "Skip", onSkipClick, this->dispatcher));
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
/// @param deltaTime
/// DeltaTime should be used when calculating timers/manual movements
void ChapterScene::onUpdate(float deltaTime)
{
	for (size_t i = 0; i < this->text.size(); i++)
	{
		this->text[i]->setPositionY(this->text[i]->getPositionY() - (speed_ * deltaTime));
	}
	if (text[this->text.size() - 1]->getPositionY() < 0)
	{
		moveToNextScene = true;
		nextScene = "Overworld";
	}

	if (moveToNextScene)
	{
		stateMachine->switchToScene(nextScene, useTransition, playSound);
	}

}

