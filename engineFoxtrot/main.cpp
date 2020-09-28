#pragma once
#include <iostream>
#include "Engine.h"
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

// Doxygen
// Cntrl + / above function or class to generate Doxygen
// https://devblogs.microsoft.com/cppblog/doxygen-and-xml-doc-comment-support/
// Installing
// https://computingonplains.wordpress.com/doxygen-and-visual-studio/

// TODO : Set object folder up with interface route

Engine engine;


int main() {
	engine.startTickThreads();
	
	engine.createNewSceneWithSceneID(2);
	engine.createNewSceneWithSceneID(1);

	engine.createNewObjectWithSceneID(1, 1, 50, 5, 40, 40);
	
	engine.createNewObjectWithSceneID(2, 1, 50, 5, 40, 40);
	engine.createNewObjectWithSceneID(2, 2, 100, 5, 40, 40);
	engine.createNewObjectWithSceneID(2, 3, 150, 5, 40, 40);
	engine.createNewObjectWithSceneID(2, 4, 5, 50, 40, 40);
	engine.createNewObjectWithSceneID(2, 5, 50, 50, 40, 40);
	engine.createNewObjectWithSceneID(2, 6, 100, 50, 40, 40);
	engine.createNewObjectWithSceneID(2, 7, 150, 50, 40, 40);
	engine.createNewObjectWithSceneID(2, 8, 5, 100, 40, 40);
	engine.createNewObjectWithSceneID(2, 9, 5, 100, 40, 40);
	engine.createNewObjectWithSceneID(2, 10, 50, 100, 40, 40);
	


	
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
	
	engine.setCurrentScene(2);
	this_thread::sleep_for(chrono::milliseconds(250));
	engine.createNewSceneWithSceneID(10);
	engine.setCurrentScene(10);
	this_thread::sleep_for(chrono::milliseconds(1000));
	engine.setCurrentScene(2);
	cout << "Engine filled" << endl;
	
	this_thread::sleep_for(chrono::milliseconds(2500));
	for (int i = 0; i < 10; i++)
	{
		if(i % 2)engine.setCurrentScene(1);
		else engine.setCurrentScene(2);
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	cout << "about to set" << endl;
	engine.setCurrentScene(1);
	cout << "setted" << endl;
	
	for (int i = 0; i < 100; i++)
	{
		engine.moveObjectTo(1, i, 10);
		this_thread::sleep_for(chrono::milliseconds(10));
	}

	for (int i = 0; i < 360; i++)
	{
		engine.setObjectRotation(1, i);
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	engine.setCurrentScene(1);
	engine.stopTickThreads();


	//engine.addEventListener(new PhysicsEngine, EventType::MOVE);
	//engine.eventManager.notify(EventType::MOVE, new Object);

	while (1) {}

}


