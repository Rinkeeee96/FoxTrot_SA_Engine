#pragma once
#include "api.h";

class SceneSwitcher
{
public:
    static SceneSwitcher& get_instance() { return instance; }

    // prohibit copy & move
    SceneSwitcher(const SceneSwitcher&) = delete;
    SceneSwitcher(SceneSwitcher&&) = delete;
    SceneSwitcher& operator=(const SceneSwitcher&) = delete;
    SceneSwitcher& operator=(SceneSwitcher&&) = delete;

    void RegisterScene(string const identifier, Scene* scene);
    void SwitchToScene(string const identifier);
    void SetEngine(Engine* _engine) { engine = _engine; }
    void runCurrentScene();

private:
    map<string, Scene*> scenes;
    Engine* engine;
    Scene* activeScene;
    static SceneSwitcher instance;
    SceneSwitcher(){}

    Scene* currentScene = nullptr;
};