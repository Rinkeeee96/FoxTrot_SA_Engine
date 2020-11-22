#pragma once
#include "api.h"
class GeneralTransition;

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
    void registerTransitionScene(Scene* scene);
    void switchToScene(string const identifier, bool useTransitionScreen);
    void setEngine(Engine* _engine) { engine = _engine; }
    void runCurrentScene();

private:
    map<string, Scene*> scenes;
    Engine* engine = nullptr;
    Scene* activeScene = nullptr;
    static SceneSwitcher instance;
    SceneSwitcher() {};

    bool currentlyRunningTransition = false;
};