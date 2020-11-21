#include "pch.h"
#include "SceneSwitcher.h"
#include "Game/Scenes/Transitions/GeneralTransition/GeneralTransition.h"
SceneSwitcher SceneSwitcher::instance;


void SceneSwitcher::registerScene(string const identifier, Scene* scene) { //registerScene(const string& identifier, Scene* scene) {
	if (scene == nullptr) throw exception("Scene is nullptr");
	engine->insertScene(scene);
	scenes.insert(pair<string, Scene*>(identifier, scene));
}

void SceneSwitcher::registerTransitionScene(Scene* scene)
{
	registerScene("GENERAL_TRANSITION_SCENE", scene);
}

void SceneSwitcher::switchToScene(string const identifier, bool useTransitionScreen) { //switchToScene(const string& identifier, bool useTransitionScreen) {
	if (DEBUG_MAIN) { useTransitionScreen = false; }
	auto scene = scenes.find(identifier);
	if (scene == scenes.end()) 
		throw exception("Scene is end()");
	//TODO start transitiescreen

	auto transScene = scenes.find("GENERAL_TRANSITION_SCENE");
	bool transitionSceneAvailable = true;
	transScene == scenes.end() ? transitionSceneAvailable = false : transitionSceneAvailable = true;

	if (!currentlyRunningTransition && useTransitionScreen && transitionSceneAvailable)
	{
		currentlyRunningTransition = true;
		engine->setCurrentScene(scenes["GENERAL_TRANSITION_SCENE"]->getSceneID());
		scene = scenes.find("GENERAL_TRANSITION_SCENE");
		((GeneralTransition*)scene->second)->setNextScene(identifier);
	}
	else
	{
		engine->setCurrentScene(scene->second->getSceneID());
		currentlyRunningTransition = false;
	}

	// Detach the old now inactive scene
	if (activeScene != nullptr)
	{
		activeScene->onDetach();
	}

	scene->second->onAttach();
	scene->second->start();
			
	// Set the new scene active
	activeScene = scene->second;
}

/// @brief 
/// Runs the current scene
void SceneSwitcher::runCurrentScene()
{
	if (activeScene == nullptr) return;

	activeScene->onUpdate();
}