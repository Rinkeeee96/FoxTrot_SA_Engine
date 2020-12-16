#include "stdafx.h"
#include "Scene.h"
#include "SceneManager\Objects\Drawable.h"
#include "Events/Key/KeyPressed.h"

#define POP_UP_DEFAULT_WIDTH	400
#define POP_UP_DEFAULT_HEIGHT	150

/// @brief 
/// @param sceneID 
Scene::Scene(const int _sceneID, const int _sceneHeight, const int _sceneWidth) : 
	sceneID(_sceneID), sceneHeight(_sceneHeight), sceneWidth(_sceneWidth)
{
}

/// @brief 
Scene::~Scene()
{
}

/// @brief 
/// Function for checking if an object with ObjectID exists in a Scene.
/// @param objectID 
/// Identifier for a ObjectID
/// @return 
/// Returns true if Object is found in current scene else false.
bool Scene::checkIfObjectExists(const int objectID)
{
	bool exists = false;
	for (auto layer : layers)
	{
		exists = layer.second->objectExists(objectID);
	}
	return exists;
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
		if (render)
		{
			layers[zIndex]->onAttach();
		} else {
			layers[zIndex]->onDetach();
		}

		layers[zIndex]->setRender(render);
		return render;
	}
	return false;
}

/// @brief 
/// Returns a filtered collection of all the drawables in the current scene TEMPORARY
/// @return 
vector <Drawable*> Scene::getAllDrawablesInScene()
{
	vector <Drawable*> returnVector;
	for (auto layer : layers)
	{
		for (auto obj : layer.second->objects)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(obj.second);
			if (drawable != nullptr)
				returnVector.push_back(drawable);
		}
	}
	return returnVector;
}

/// @brief 
/// Returns pointers to all available objects in the whole scene. 
/// @return 
vector <Object*> Scene::getAllObjectsInScene()
{
	vector <Object*> returnVector;
	for (auto layer : layers)
	{
		for (auto obj : layer.second->objects)
		{
			if (obj.second != nullptr)
			{
				returnVector.push_back(obj.second);
			}
		}
	}
	return returnVector;
}

/// @brief Returns all objects in the scene with the renderPhysics value on true
/// @return 
vector <Object*> Scene::getAllObjectsInSceneRenderPhysics()
{
	vector <Object*> returnVector;
	for (auto layer : layers)
	{
		if (layer.second->getRenderPhysics()) {
			for (auto obj : layer.second->objects) {
				returnVector.push_back(obj.second);
			}
		}
	}
	return returnVector;
}

/// @brief 
/// Adds a new object to the given Z index. 
/// @param zIndex 
/// Zindex of the layer that the object should be added to
/// @param object 
/// Pointer to the object
const void Scene::addNewObjectToLayer(const int zIndex, Object* object, bool renderPhysics, bool alwaysDrawLayer)
{
	if (object == nullptr) throw ERROR_CODE_SCENE_NO_OBJECT_FOUND;

	if (layers.find(zIndex) != layers.end())
	{
		layers[zIndex]->addObjectInLayer(object);
	}
	else
	{
		layers[zIndex] = new Layer();
		layers[zIndex]->setRenderPhysics(renderPhysics);
		layers[zIndex]->addObjectInLayer(object);
		layers[zIndex]->setAlwaysVisible(alwaysDrawLayer);
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
	for (auto layer : layers)
	{
		if (layer.second->objectExists(objectID))
		{
			return layer.second->getSpecificObjectInLayer(objectID);
		}
	}
	throw exception("object does not exist");
}

/// @brief Deletes all objects in the scene when called.
void Scene::onDetach()
{
	for (auto& layerContainer : layers)
	{
		Layer* layer = layerContainer.second;
		for (auto obj : layer->objects)
			delete obj.second;

		layer->clearObjects();
		delete layer;
	}
	layers.clear();
}

/// @brief 
/// Returns the id of the object to follow
/// @return 
/// If no ObjectToFollow will return -1
int Scene::getObjectToFollowID() const
{
	if (objectToFollow != nullptr)
	{
		return objectToFollow->getObjectId();
	}
	else
	{
		return -1;
	}

}

/// @brief Removes a specific object from the current scene
/// @param obj 
void Scene::removeObjectFromScene(Object* obj)
{
	for (auto lay : layers) {
		if (lay.second->objectExists(obj->getObjectId())) {
			lay.second->removeObject(obj->getObjectId());
			obj->setIsRemoved(true);
			return;
		}
	}
}

/// @brief Returns the layers map in a scene
/// @return 
map<int, Layer*> Scene::getLayers() const
{
	return layers;
}

/// @brief Create a layer on the active scene with the given zIndex
/// @param zIndex 
/// @param renderPhysics 
/// @param alwaysDrawLayer 
void Scene::createLayer(const int zIndex, bool renderPhysics, bool alwaysDrawLayer)
{
	layers[zIndex] = new Layer();
	layers[zIndex]->setRenderPhysics(renderPhysics);
	layers[zIndex]->setAlwaysVisible(alwaysDrawLayer);
}

/// @brief Finds the highest layer zIndex in the scene.
/// @return 
int Scene::getHighestLayerIndex() {
	int zIndex = 0;

	// Get highest zIndex
	for (auto layer : layers) {
		if (zIndex < layer.first)
			zIndex = layer.first;
	}
	return zIndex;
}

/// @brief Creates a basic l with text
/// @param xPosition 
/// @param yPosition 
/// @param text 
int Scene::addLayerOnHighestZIndex(Layer* _layer) 
{
	int zIndex = getHighestLayerIndex() + 1;
	layers[zIndex] = _layer;
	return zIndex;
}

/// @brief 
/// @param zIndex 
/// @param _layer 
void Scene::addLayerOnZIndex(const int zIndex, Layer* _layer)
{
	layers[zIndex] = _layer;
}

/// @brief remove layer
/// @param _zIndex no value means top layer.
void Scene::removeLayer(const int zIndex) 
{
	if (layers.count(zIndex) > 0)
	{
		layers.erase(zIndex);
	}
}
