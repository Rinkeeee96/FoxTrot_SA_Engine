#include "glpch.h"
#include "Scene.h"
namespace Glitch {

	/// @brief 
	/// @param sceneID 
	Scene::Scene(int sceneID)
	{
		this->sceneID = sceneID;
	}

	/// @brief 
	Scene::~Scene()
	{
	}

	void Scene::addNewObject(Object* object) {
		objects.push_back(object);
	}

	/// @brief 
	/// @param id 
	/// @param xPos 
	/// @param yPos 
	/// @param height 
	/// @param width 
	void Scene::addNewObject(int id, int xPos, int yPos, int height, int width)
	{
		objects.push_back(new Object(id, xPos, yPos, height, width));
	}

	/// @brief 
	/// @param ObjectID 
	/// @return 
	Object* Scene::getObject(int spriteID)
	{
		for (Object* obj : objects)
		{
			if (obj->getSpriteID() == spriteID)
			{
				return obj;
			}
		}
		throw ERROR_CODE_SCENE_NO_OBJECT_FOUND;
	}

}