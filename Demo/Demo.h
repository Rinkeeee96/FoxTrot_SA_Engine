#pragma once
#include "pch.h"
#include "MainScene.h"

int main() {
    Engine engine;
    EventDispatcher dispatcher;
    MainScene* scene = new MainScene(engine);

    engine.insertScene(scene);
    engine.setCurrentScene(scene->getSceneID());
    scene->start(true);

    engine.setEngineRunning(true);

    while (engine.getEngineRunning()) {
        engine.updateFps();
        engine.onUpdate();

        engine.getCurrentScene()->onUpdate();

        this_thread::sleep_for(chrono::milliseconds(10));
        engine.updateFps();
    }

    return 0;
}