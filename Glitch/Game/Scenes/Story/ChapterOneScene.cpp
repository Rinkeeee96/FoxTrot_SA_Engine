#include "pch.h"
#include "ChapterOneScene.h"
#include "Game/SpriteState.h"
#include "Game/Buttons/PrimaryButton.h"
#include "Game/Buttons/SecondaryButton.h"
#include "Game/Game.h"

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)
#define BIND_FN(function) std::bind(&ChapterOneScene::function, *this)

void ChapterOneScene::onAttach()
{
	loadButtons();
	loadText();
	loadBackground();
	loadMusic();

	dispatcher.setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(ChapterOneScene::onKeyPressed));
}

bool ChapterOneScene::onKeyPressed(const Event& event)
{
	auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);

	switch (keyPressedEvent.GetKeyCode())
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

vector<string> splitToLines(string stringToSplit, int maximumLineLength)
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
			int x = ret[ret.size() - 1].length();
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

vector<Text*> splitText(string text) {
	auto startingId = 4;
	auto startingPos = -200;

	vector<Text*> ret;
	std::string delimiter = "\n";

	size_t pos = 0;
	std::string token;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		token = text.substr(0, pos);

		auto result = splitToLines(token, 81);
		int i = 0;
		for (size_t i = 0; i < result.size(); i++)
		{
			startingPos = startingPos + TEXT_HEIGHT;
			ret.push_back(new Text(startingId++, new ColoredText(result[i], Color(255, 255, 255), false), (WINDOW_WIDTH / 81) * result[i].length(),
				TEXT_HEIGHT, 0, WINDOW_HEIGHT + startingPos));
		}
		text.erase(0, pos + delimiter.length());
	}
	return ret;
}

/// @brief 
/// Create all text for this scene
void ChapterOneScene::loadText() {
	auto comp = splitText(" Je wordt wakker in een vreemde wereld en je weet niet meer waar je je bevindt.... \n Je hoort een bekende stem ... ... ... \n ... \n ... \n ... \n  \n Ah het is Bob van der Putten! \n  \n  Je kan Bob nog goed herinneren van de geweldige lessen die je op het Avans van hem hebt gehad. \n  \n Je vraag Bob wat er is gebeurd en zegt dat je je niks kan herrineren, het laatste wat je je kan herrineren was dat je bezig was voor je minor, een fantastische game ontwikkelen. \n   \n Bob; Helaas kan ik mij ook niks meer herrineren, ik ben al wat langer wakker en heb vast wat kunnen voor verkennen. In deze wereld begeven zich vreemde wezens en landen. \n  \n Om eruit te komen zullen wij op avontuur moeten gaan! \n Laten we beginnen bij het eerste gebied \n");
	
	this->text = comp;
	for (size_t i = 0; i < this->text.size(); i++)
	{
		addNewObjectToLayer(2, this->text[i], false, true);
	}
}

/// @brief 
/// Create all buttons for this scene
void ChapterOneScene::loadButtons() {
	// Back button
	auto* backBtn = new SecondaryButton(3, "Skip", BIND_FN(onSkipClick), this->dispatcher);
	backBtn->setPositionX(WINDOW_WIDTH - 40 - backBtn->getWidth());
	backBtn->setPositionY(WINDOW_HEIGHT - 10 - backBtn->getHeight());

	addNewObjectToLayer(4, backBtn);
}

/// @brief 
/// Create the background for this scene
void ChapterOneScene::loadBackground() {
	SpriteObject* bg0 = new SpriteObject(-33, 1080, 1920, 1, 300, "Assets/Backgrounds/dark_bg.png");
	auto* bgLayer0 = new Drawable(0);
	bgLayer0->setStatic(true);
	bgLayer0->setPositionX(0);
	bgLayer0->setPositionY(1080);
	bgLayer0->setWidth(1920);
	bgLayer0->setHeight(1080);
	bgLayer0->registerSprite(SpriteState::DEFAULT, bg0);
	bgLayer0->changeToState(SpriteState::DEFAULT);

	SpriteObject* fgB = new SpriteObject(-34, 1080, 1920, 1, 300, "Assets/Backgrounds/foreground_bottom.png");
	auto* fgBLayer = new Drawable(1);
	fgBLayer->setStatic(true);
	fgBLayer->setPositionX(0);
	fgBLayer->setPositionY(1080);
	fgBLayer->setWidth(1920);
	fgBLayer->setHeight(200);
	fgBLayer->registerSprite(SpriteState::DEFAULT, fgB);
	fgBLayer->changeToState(SpriteState::DEFAULT);

	SpriteObject* fgT = new SpriteObject(-35, 1080, 1920, 1, 300, "Assets/Backgrounds/foreground_top.png");
	auto* fgTLayer = new Drawable(2);
	fgTLayer->setStatic(true);
	fgTLayer->setPositionX(0);
	fgTLayer->setPositionY(100);
	fgTLayer->setWidth(1920);
	fgTLayer->setHeight(100);
	fgTLayer->registerSprite(SpriteState::DEFAULT, fgT);
	fgTLayer->changeToState(SpriteState::DEFAULT);

	addNewObjectToLayer(0, bgLayer0, false, true);
	addNewObjectToLayer(3, fgTLayer, false, true);
	addNewObjectToLayer(3, fgBLayer, false, true);
}

/// @brief 
/// Load the sounds for this scene
void ChapterOneScene::loadMusic() {
	engine.soundEngine.onLoadBackgroundMusicEvent("WIN_SOUND", "Assets/Sound/TremLoadingloopl.wav");
}

/// @brief 
/// Create the sounds for this scene
void ChapterOneScene::start(bool playSound)
{
	if (playSound)engine.soundEngine.onStartBackgroundMusicEvent("WIN_SOUND");
	this->speed_ = 1;
}

void ChapterOneScene::onUpdate()
{
	for (size_t i = 0; i < this->text.size(); i++)
	{
		this->text[i]->setPositionY(this->text[i]->getPositionY() - speed_);
		if (text[this->text.size() - 1]->getPositionY() < 0) stateMachine.switchToScene("Overworld", false);
	}
}

/// @brief 
/// Remove the sounds of the soundengine
void ChapterOneScene::onDetach()
{
	engine.soundEngine.onStartBackgroundMusicEvent("WIN_SOUND");
	Scene::onDetach();
}

/// @brief 
/// A callback function for overworldBTN
/// Start transition scene to overworl
void ChapterOneScene::onSkipClick() {
	stateMachine.switchToScene("Overworld", false);
}
