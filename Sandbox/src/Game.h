#pragma once
#include "Glitch.h"
class Game : public Glitch::Application
{
public:
	Game() {
		sceneManager.createNewScene(1);
;
		renderer->loadSingleSprite(1, "../Assets/Sprites/World/LIGHT TILE WITHOUT TOP.png");


		renderer->loadSingleSprite(100, "../Assets/Sprites/Character/adventure.png");
		renderer->loadSprite(101, "../Assets/Sprites/Character/adventure_air_attack1.png", 37, 50, 4);
		renderer->loadSprite(102, "../Assets/Sprites/Character/adventure_run.png", 37, 50, 6);
		renderer->loadSprite(103, "../Assets/Sprites/Character/adventure_slide.png", 37, 50, 2);

		Glitch::Object* object = new Glitch::Object(100);
		object->setName("character");
		object->setHeight(200);
		object->setWidth(200);
		object->setPositionX(30);
		object->setPositionY(80);
		object->setSpeed(100);
		object->setJumpHeight(400);
		object->setDensity(10);
		object->setFriction(0);
		object->setRestitution(0);
		object->setStatic(false);
		object->registerSprite("air_attack", 101);
		object->registerSprite("run", 102);
		object->registerSprite("slide", 103);
		object->changeToState("run");
		sceneManager.getSceneWithID(1)->addNewObject(object);

		Glitch::Object* staticGround = new Glitch::Object(1);
		staticGround->setWidth(500); // width
		staticGround->setHeight(10);// height
		staticGround->setPositionX(20); // x 20 left down
		staticGround->setPositionY(300);// y 300 left down
		staticGround->setStatic(true);
		sceneManager.getSceneWithID(1)->addNewObject(staticGround);

		sceneManager.setCurrentScene(1);

		physics.registerObjectInCurrentVectorWithPhysicsEngine();
	};
	~Game() {};
};