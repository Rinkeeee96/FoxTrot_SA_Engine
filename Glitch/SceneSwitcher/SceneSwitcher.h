#pragma once

#include "api.h"

class SceneSwitcher
{
public:
	SceneSwitcher(Engine& _engine) : engine(_engine) {};
	~SceneSwitcher() {};

	void RegisterScene(string const identifier, Scene* scene);
	void SwitchToScene(string const identifier);
private:
	map<string, Scene*> scenes;
	Engine& engine;
};