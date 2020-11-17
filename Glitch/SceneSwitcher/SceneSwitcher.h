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

    void registerScene(string const identifier, Scene* scene);
    void switchToScene(string const identifier);
    void setEngine(Engine* _engine) { engine = _engine; }
    void runCurrentScene();

private:
    map<string, Scene*> scenes;
    Engine* engine;
    Scene* activeScene;
    static SceneSwitcher instance;
    SceneSwitcher(){}

};