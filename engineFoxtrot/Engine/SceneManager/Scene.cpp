#include "stdafx.h"
#include "Scene.h"

/// @brief 
/// @param sceneID 
Scene::Scene(const int id, int _sceneHeight, int _sceneWidth) : sceneID(id), sceneHeight(_sceneHeight), sceneWidth(_sceneWidth)
{

}

/// @brief 
Scene::~Scene()
{
}

/// @brief 
/// @param ObjectID 
/// @return 
Object* Scene::getObjectWithID(const int ObjectID)
{
	for (Object* obj : getAllObjectsInScene())
	{
		if (obj->getObjectId() == ObjectID)
		{
			return obj;
		}
	}
	// Todo throw error
	return nullptr;
}

/// @brief 
/// Function for checking if an object with ObjectID exists in a Scene.
/// @param objectID 
/// Identifier for a ObjectID
/// @return 
/// Returns true if Object is found in current scene else false.
bool Scene::checkIfObjectExists(const int objectID)
{
	for (Object* obj : getAllObjectsInScene())
	{
		if (obj->getObjectId() == objectID)
		{
			return true;
		}
	}
	return false;
}

/// @brief 
/// Turns the layer on or off
/// @param zIndex 
/// The zindex of the layer to be toggled
/// @param render 
/// True for on, false for off
/// @return 
/// Returns the new state of the layer.
/// False in case the layer is not available. 
const bool Scene::toggleLayer(const int zIndex, bool render)
{
	if (layers.find(zIndex) != layers.end())
	{
		layers[zIndex]->render = render;
		return render;
	}
	return false;
}

/// @brief 
/// Returns pointers to all available objects in the whole scene. 
/// @return 
vector <Object*> Scene::getAllObjectsInScene()
{
	vector <Object*> returnVector;
	for (auto layer = layers.begin(); layer != layers.end(); layer++)
	{
		returnVector.insert(returnVector.end(), (*layer).second->objects.begin(), (*layer).second->objects.end());
	}
	return returnVector;
}

/// @brief 
/// Adds a new object to the given Z index. 
/// @param zIndex 
/// Zindex of the layer that the object should be added to
/// @param object 
/// Pointer to the object
const void Scene::addNewObjectToLayer(const int zIndex, Object* object)
{
	if (object == nullptr) throw ERROR_CODE_SCENE_NO_OBJECT_FOUND;

	if (layers.find(zIndex) != layers.end()) 
	{
		layers[zIndex]->objects.push_back(object);
	}
	else 
	{
		layers[zIndex] = new Layer();
		layers[zIndex]->objects.push_back(object);
	}
}

/// @brief 
/// Returns the object matched with the given objectID, if none are found an error is thrown
/// @param ObjectID 
/// Identifier for objectID
/// @return 
/// Returns pointer to the found Object
Object * Scene::getObject(const int objectID)
{
	for (Object * obj : getAllObjectsInScene())
	{
		if (obj->getObjectId() == objectID)
		{
			return obj;
		}
	}
	throw ERROR_CODE_SCENE_NO_OBJECT_FOUND;
}

void Scene::setSceneWidth(int width)
{
	sceneWidth = width;
}

int Scene::getSceneWidth() const
{
	return sceneWidth;
}

void Scene::setSceneHeight(int height)
{
	sceneHeight = height;
}

int Scene::getSceneHeight() const
{
	return sceneHeight;
}
