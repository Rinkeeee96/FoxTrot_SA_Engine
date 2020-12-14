#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

#define NUMBER_OF_CHARACTERS_ON_LINE 70
#define TEXT_SIZE_DIVIDER 80
#define START_Y_POS -200
#define MAX_SPEED 10

/// @brief Base class for the chapter screen
class ChapterScene : public GameScene
{
public:
	ChapterScene(const int id, unique_ptr<Engine>& _engine, SceneStateMachine& _statemachine);
	virtual ~ChapterScene() { };
	// Inherited via Scene
	virtual void onAttach() override {};
	virtual void start(bool playSound) override {};
	virtual void onUpdate() override;
	virtual void onDetach() override { Scene::onDetach(); };

	bool onKeyPressed(const Event& event);

protected:
	vector<Text*> text;
	FileLoader fileLoader;

	virtual void setTextFromFile(string path, int startingId);
	virtual void loadText() {};
	virtual void loadBackground() {};
	virtual void loadMusic() {};

	void loadButtons();
	void onSkipClick();

	vector<string> splitToLines(string stringToSplit, int maximumLineLength);
	vector<Text*> splitText(string text, int startingId);
	int speed_ = 1;
};
