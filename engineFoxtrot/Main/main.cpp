#include "stdafx.h"
#pragma once
#include "../Engine/Engine.h"


using namespace std;

// TODO engine.h & engine.cpp

// Doxygen
// Cntrl + / above function or class to generate Doxygen
// https://devblogs.microsoft.com/cppblog/doxygen-and-xml-doc-comment-support/
// Installing
// https://computingonplains.wordpress.com/doxygen-and-visual-studio/

Engine engine;

void sceneTestSetup()
{
	engine.addEventListener(new PhysicsEngine, EventType::MOVE);
	engine.eventManager.notify(EventType::MOVE, new Object(1));

	engine.linkSpriteIDWithAssetPath(1, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-air-attack1-00.png");
	engine.linkSpriteIDWithAssetPath(2, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-air-attack1-01.png");
	engine.linkSpriteIDWithAssetPath(3, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-air-attack1-02.png");
	engine.linkSpriteIDWithAssetPath(4, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-air-attack1-03.png");
	engine.linkSpriteIDWithAssetPath(5, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-attack1-00.png");
	engine.linkSpriteIDWithAssetPath(6, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-attack1-01.png");
	engine.linkSpriteIDWithAssetPath(7, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-attack1-02.png");
	engine.linkSpriteIDWithAssetPath(8, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-attack1-03.png");
	engine.linkSpriteIDWithAssetPath(9, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-attack1-04.png");
	engine.linkSpriteIDWithAssetPath(10, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/helmet_02a.png");
	engine.linkSpriteIDWithAssetPath(101, "../Assets/Sprites/Project assets/LIGHT TILE WITHOUT TOP.png");

	Scene* testScene = new Scene(3);

	Object* object = new Object(1);
	object->setName("house");
	object->setHeight(80);
	object->setWidth(80);
	object->setPositionX(30);
	object->setPositionY(80);
	object->setSpeed(100);
	object->setJumpHeight(400);
	object->setDensity(10);
	object->setFriction(0);
	object->setRestitution(0);
	object->setStatic(false);

	testScene->addNewObjectToLayer("OneLayer", object);
	
	Object* object2 = new Object(2);
	object2->setName("person");
	object2->setHeight(80);
	object2->setWidth(80);
	object2->setPositionX(100);
	object2->setPositionY(80);
	object2->setSpeed(100);
	object2->setJumpHeight(400);
	object2->setDensity(10);
	object2->setFriction(0);
	object2->setRestitution(0);
	object2->setStatic(false);
	testScene->addNewObjectToLayer("OneLayer", object2);

	Object* staticGround = new Object(101);
	staticGround->setWidth(500); // width
	staticGround->setHeight(10);// height
	staticGround->setPositionX(20); // x 20 left down
	staticGround->setPositionY(300);// y 300 left down
	staticGround->setStatic(true);
	testScene->addNewObjectToLayer("OneLayer", staticGround);
	
	engine.insertScene(testScene);
	engine.insertScene(new Scene(4));

	engine.setCurrentScene(3);
	engine.startTickThreads();
}

int main() {
	sceneTestSetup();
	this_thread::sleep_for(chrono::milliseconds(3000));
	engine.setCurrentScene(4);
	this_thread::sleep_for(chrono::milliseconds(3000));
	engine.setCurrentScene(3);



	bool gameRunning = true;
	while (gameRunning)
	{

	}

	return 0;
}