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

/// @brief 
/// Create all text for this scene
void ChapterOneScene::loadText() {
	auto* text4 = new Text(4, new ColoredText("Je wordt wakker in een vreemde wereld en je weet niet meer waar je je bevindt....", Color(255, 255, 255), false), WINDOW_WIDTH, TEXT_HEIGHT, 0, WINDOW_HEIGHT - 1100);
	auto* text5 = new Text(5, new ColoredText("Je hoort een bekende stem ... ... ...", Color(255, 255, 255), false), WINDOW_WIDTH / 2, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text6 = new Text(6, new ColoredText("...", Color(255, 255, 255), false), 50, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text7 = new Text(7, new ColoredText("...", Color(255, 255, 255), false), 50, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text8 = new Text(8, new ColoredText("...", Color(255, 255, 255), false), 50, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text9 = new Text(9, new ColoredText("", Color(255, 255, 255), false), 100, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text10 = new Text(10, new ColoredText("Ah het is Bob van der Putten!", Color(255, 255, 255), false), WINDOW_WIDTH / 2, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text11 = new Text(11, new ColoredText("", Color(255, 255, 255), false), 50, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text12 = new Text(12, new ColoredText("je kan Bob nog goed herinneren van de geweldige lessen die je op het Avans van ", Color(255, 255, 255), false), WINDOW_WIDTH, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text13 = new Text(13, new ColoredText("hem hebt gehad.", Color(255, 255, 255), false), WINDOW_WIDTH / 4, TEXT_HEIGHT, 0, WINDOW_HEIGHT);

	auto* text14 = new Text(14, new ColoredText("", Color(255, 255, 255), false), 50, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text15 = new Text(15, new ColoredText("Je vraag Bob wat er is gebeurd en zegt dat je je niks kan herrineren, het laatste wat je", Color(255, 255, 255), false), WINDOW_WIDTH, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text16 = new Text(16, new ColoredText("je kan herrineren was dat je bezig was voor je minor, een fantastische game ontwikkelen.", Color(255, 255, 255), false), WINDOW_WIDTH, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text17 = new Text(17, new ColoredText("", Color(255, 255, 255), false), 50, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text18 = new Text(18, new ColoredText("Bob; Helaas kan ik mij ook niks meer herrineren, ik ben al wat langer wakker dan jij", Color(255, 255, 255), false), WINDOW_WIDTH, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text19 = new Text(19, new ColoredText("en heb vast wat kunnen voor verkennen. In deze wereld begeven zich vreemde wezens en landen.", Color(255, 255, 255), false), WINDOW_WIDTH, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text20 = new Text(20, new ColoredText("", Color(255, 255, 255), false), 50, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text21 = new Text(21, new ColoredText("Om eruit te komen zullen wij op avontuur moeten gaan!", Color(255, 255, 255), false), WINDOW_WIDTH /2, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text22 = new Text(22, new ColoredText("", Color(255, 255, 255), false), 50, TEXT_HEIGHT, 0, WINDOW_HEIGHT);
	auto* text23 = new Text(23, new ColoredText("Laten we beginnen bij het eerste gebied", Color(255, 255, 255), false), WINDOW_WIDTH / 3, TEXT_HEIGHT, 0, WINDOW_HEIGHT);

	this->text.push_back(text4);
	this->text.push_back(text5);
	this->text.push_back(text6);
	this->text.push_back(text7);
	this->text.push_back(text8);
	this->text.push_back(text9);
	this->text.push_back(text10);
	this->text.push_back(text11);
	this->text.push_back(text12);
	this->text.push_back(text13);
	this->text.push_back(text14);
	this->text.push_back(text15);
	this->text.push_back(text16);
	this->text.push_back(text17);
	this->text.push_back(text18);
	this->text.push_back(text19);
	this->text.push_back(text20);
	this->text.push_back(text21);
	this->text.push_back(text22);
	this->text.push_back(text23);

	int YAdder = 200;
	for (size_t i = 0; i < this->text.size(); i++)
	{
		if(i!=0)this->text[i]->setPositionY(this->text[i - 1]->getPositionY() + TEXT_HEIGHT);
		addNewObjectToLayer(2, this->text[i], false, true);
	}
}
/// @brief 
/// Create all buttons for this scene
void ChapterOneScene::loadButtons() {
	// Back button
	auto* backBtn = new SecondaryButton(3, "Overworld", BIND_FN(onSkipClick), this->dispatcher);
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
		//this->text[i]->setPositionY(this->text[i]->getPositionY() - 1);
		this->text[i]->setPositionY(this->text[i]->getPositionY() - speed_);
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
	stateMachine.switchToScene("Overworld", true);
}
