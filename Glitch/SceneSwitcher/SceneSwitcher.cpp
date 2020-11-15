#include "SceneSwitcher.h"
SceneSwitcher SceneSwitcher::instance;


void SceneSwitcher::RegisterScene(string identifier, Scene* scene) {
	if (scene == nullptr)return;
	engine->insertScene(scene);
	scenes.insert(pair<string, Scene*>(identifier, scene));
}

void SceneSwitcher::SwitchToScene(string const identifier) {
	auto scene = scenes.find(identifier);
	if (scene == scenes.end())return;
	//TODO start transitiescreen
	engine->setCurrentScene(scene->second->getSceneID());

	currentScene = scenes[identifier];
}

void SceneSwitcher::runCurrentScene()
{
	if (!currentScene) return;

	currentScene->run();
}