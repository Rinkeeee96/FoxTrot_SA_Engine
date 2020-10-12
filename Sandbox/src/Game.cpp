#include "Glitch.h"
#include <Glitch\Core\Object.cpp>

class Game : public Glitch::Application
{
public:
	Game() {
		sceneManager->createNewScene(1);
		sceneManager->createNewScene(2);
		sceneManager->createNewScene(3);
		sceneManager->createNewScene(20);

		sceneManager->getSceneWithID(1)->addNewObject(1, 1, 1, 1, 1);
		sceneManager->setCurrentScene(1);

		sceneManager->getSceneWithID(1)->addNewObject(2, 1, 50, 50, 40);
		sceneManager->getSceneWithID(1)->addNewObject(2, 2, 100, 50, 40);
		sceneManager->getSceneWithID(1)->addNewObject(2, 3, 150, 50, 40);
		sceneManager->getSceneWithID(1)->addNewObject(2, 4, 200, 50, 40);
		sceneManager->getSceneWithID(1)->addNewObject(2, 5, 250, 50, 40);
		sceneManager->getSceneWithID(1)->addNewObject(2, 6, 50, 100, 40);
		sceneManager->getSceneWithID(1)->addNewObject(2, 7, 150, 100, 40);
		sceneManager->getSceneWithID(1)->addNewObject(2, 8, 200, 100, 40);
		sceneManager->getSceneWithID(1)->addNewObject(2, 9, 250, 100, 40);
		sceneManager->getSceneWithID(1)->addNewObject(2, 10, 300, 100, 40);

		renderer->loadImage(1, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-air-attack1-00.png");
		renderer->loadImage(2, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-air-attack1-01.png");
		renderer->loadImage(3, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-air-attack1-02.png");
		renderer->loadImage(4, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-air-attack1-03.png");
		renderer->loadImage(5, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-attack1-00.png");
		renderer->loadImage(6, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-attack1-01.png");
		renderer->loadImage(7, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-attack1-02.png");
		renderer->loadImage(8, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-attack1-03.png");
		renderer->loadImage(9, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/adventurer-attack1-04.png");
		renderer->loadImage(10, "../Assets/Sprites/Project assets/Adventurer-1.5/Individual Sprites/helmet_02a.png");
		renderer->loadImage(101, "../Assets/Sprites/Project assets/LIGHT TILE WITHOUT TOP.png");

		Glitch::Object* object = new Glitch::Object(1);
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
		sceneManager->getSceneWithID(3)->addNewObject(object);

		Glitch::Object* staticGround = new Glitch::Object(101);
		staticGround->setWidth(500); // width
		staticGround->setHeight(10);// height
		staticGround->setPositionX(20); // x 20 left down
		staticGround->setPositionY(300);// y 300 left down
		staticGround->setStatic(true);
		sceneManager->getSceneWithID(3)->addNewObject(staticGround);


		sceneManager->setCurrentScene(3);
		std::vector<Glitch::Object*> o = sceneManager->getSceneWithID(3)->getPtrToObjects();
		physics.pointerToObjectVector = &o;
		physics.registerObjectInCurrentVectorWithPhysicsEngine();
	};
	~Game() {};
};
Glitch::Application* Glitch::CreateApplication() {
	return new Game();
}
