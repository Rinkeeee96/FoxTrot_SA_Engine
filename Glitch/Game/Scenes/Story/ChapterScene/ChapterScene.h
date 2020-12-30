#pragma once
#include "api.h"
#include "SceneManager/Objects/Button.h"
#include "Game/Scenes/GameScene.h"
#include "Game/General/GeneralGameDefines.h"

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
