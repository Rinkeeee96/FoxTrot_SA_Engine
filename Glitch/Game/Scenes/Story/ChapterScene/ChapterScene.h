#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"

#define CENTER_X  (WINDOW_WIDTH / 2)
#define CENTER_Y (WINDOW_HEIGHT / 2)

#define SHORT_NAME_WIDTH 300
#define LONG_NAME_WIDTH 350
#define LEFT_X_CENTER 500
#define RIGHT_X_CENTER 50
#define TEXT_HEIGHT 50
#define BASE_TEXT_SPEED 80
#define NUMBER_OF_CHARACTERS_ON_LINE 70
#define TEXT_SIZE_DIVIDER 80
#define TEXT_SIZE_DIVIDER_HELP 50
#define START_Y_POS -200
#define MAX_SPEED 200
#define TEXT_SPEED_INCREMENT 10

/// @brief Base class for the chapter screen
class ChapterScene : public GameScene
{
public:
	ChapterScene(const int id, unique_ptr<Engine>& _engine, shared_ptr<SceneStateMachine> _statemachine);
	virtual ~ChapterScene() { };
	// Inherited via Scene
	virtual void onAttach() override {};
	virtual void start(bool playSound) override {};
	virtual void onUpdate(float deltaTime) override;
	virtual void onDetach() override { Scene::onDetach(); };

	bool onKeyPressed(const Event& event);

protected:
	vector<shared_ptr<Text>> text;
	FileLoader fileLoader;

	virtual void setTextFromFile(string path, int startingId);
	virtual void loadText() {};
	virtual void loadBackground() {};
	virtual void loadMusic() {};

	void loadButtons();

	function<void(void)> onSkipClick = [this]() {
		moveToNextScene = true;
		nextScene = "Overworld";
	};

	vector<string> splitToLines(string stringToSplit, int maximumLineLength);
	vector<shared_ptr<Text>> splitText(string text, int startingId);
	int speed_ = 1;
};
