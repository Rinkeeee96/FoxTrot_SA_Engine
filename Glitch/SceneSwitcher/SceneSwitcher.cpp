#include "pch.h"
#include "SceneSwitcher.h"
#include "Game/Scenes/Transitions/GeneralTransition/GeneralTransition.h"
SceneSwitcher SceneSwitcher::instance;


void SceneSwitcher::RegisterScene(string identifier, Scene* scene) {
	if (scene == nullptr)return;
	engine->insertScene(scene);
	scenes.insert(pair<string, Scene*>(identifier, scene));
}

void SceneSwitcher::RegisterTransitionScene(Scene* scene)
{
	RegisterScene("GENERAL_TRANSITION_SCENE", scene);
}

void SceneSwitcher::SwitchToScene(string const identifier, bool useTransitionScreen) {
	auto scene = scenes.find(identifier);
	if (scene == scenes.end()) 
		return;
	//TODO start transitiescreen

	if (!currentlyRunningTransition && useTransitionScreen)
	{
		auto transScene = scenes.find("GENERAL_TRANSITION_SCENE");
		if (transScene == scenes.end())
		{
			// Todo find different way
			goto noTransScene;
		}

		currentlyRunningTransition = true;
		engine->setCurrentScene(scenes["GENERAL_TRANSITION_SCENE"]->getSceneID());
		scene = scenes.find("GENERAL_TRANSITION_SCENE");
		((GeneralTransition*)scene->second)->setNextScene(identifier);
	}
	else
	{
		noTransScene:
		engine->setCurrentScene(scene->second->getSceneID());
		currentlyRunningTransition = false;
	}
	scene->second->OnAttach();
	scene->second->Start();

	// Detach the old now inactive scene
	if (activeScene != nullptr)
	{
		activeScene->OnDetach();
	}
		
	// Set the new scene active
	activeScene = scene->second;
}

/// @brief 
/// Runs the current scene
void SceneSwitcher::runCurrentScene()
{
	if (activeScene == nullptr) return;

	activeScene->update();

}