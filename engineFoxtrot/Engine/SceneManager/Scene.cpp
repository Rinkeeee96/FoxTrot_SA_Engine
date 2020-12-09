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
	dispatcher.setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(Scene::onKeyPressed));
}

/// @brief 
Scene::~Scene()
{
	//for (auto layer : layers)
	//{
	//	for (auto obj : layer.second->objects)
	//	{
	//		delete obj.second;
	//	}
	//}
}

/// @brief 
/// Function for checking if an object with ObjectID exists in a Scene.
/// @param objectID 
/// Identifier for a ObjectID
/// @return 
/// Returns true if Object is found in current scene else false.
bool Scene::checkIfObjectExists(const int objectID)
{
	for (auto layer : layers)
	{
		if (layer.second->getObjectsInLayer().find(objectID) != layer.second->getObjectsInLayer().end())
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
		for (auto obj : layer.second->getObjectsInLayer())
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
		for (auto obj : layer.second->getObjectsInLayer())
		{
			if (obj.second != nullptr)
			{
				returnVector.push_back(obj.second);
			}
		}
	}
	return returnVector;
}
vector <Object*> Scene::getAllObjectsInSceneRenderPhysics()
{
	vector <Object*> returnVector;
	for (auto layer : layers)
	{
		if (layer.second->getRenderPhysics()) {
			for (auto obj : layer.second->getObjectsInLayer()) {
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
		layers[zIndex]->addObjectToLayer(object->getObjectId(), object);
	}
	else
	{
		layers[zIndex] = new Layer();
		layers[zIndex]->setRenderPhysics(renderPhysics);
		layers[zIndex]->addObjectToLayer(object->getObjectId(), object);
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
	throw ERROR_CODE_SCENE_NO_OBJECT_FOUND;
}

void Scene::onDetach()
{
	for (auto& layerContainer : layers)
	{
		Layer* layer = layerContainer.second;
		for (const auto& [id, object] : layer->getObjectsInLayer())
			layer->removeObject(id);

		layer->clearObjects();
		delete layer;
	}
	layers.clear();
}

// TODO remove after command pattern is implemented
bool Scene::onKeyPressed(const Event& event) {	
	auto keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
	// TODO command pattern
	switch (keyPressedEvent.GetKeyCode())
	{
	case KeyCode::KEY_P:
		if (!hasActivePopUp) {
			//createPopUpLayer(WINDOW_WIDTH_CENTER, WINDOW_HEIGHT_CENTER, "Paused");
		}
		else {
			removeLayer();
		}
		break;
	default:
		return false;
	}
	return false;
}

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
	layers[zIndex]->setRender(renderPhysics);
	layers[zIndex]->setAlwaysVisible(alwaysDrawLayer);
}

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
void Scene::addLayer(Layer* _layer) {
	int zIndex = getHighestLayerIndex() + 1;

	layers[zIndex] = _layer;
}

/// @brief remove layer
/// @param _zIndex no value means top layer.
void Scene::removeLayer(int _zIndex) {
	if (_zIndex == -1) {
		int zIndex = 0;

		zIndex = getHighestLayerIndex();
		layers.erase(zIndex);
	}
	else {
		layers.erase(_zIndex);
	}
}
