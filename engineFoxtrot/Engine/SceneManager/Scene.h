#pragma once

#include "Objects/Object.h"
#include "Objects/Drawable.h"
#include "Layer.h"

class EventDispatcher;

/// @brief 
/// Scene Class
/// Contains all the objects that should be drawn in this scene.

class Scene 
{
public:
	API Scene(const int _sceneID, const int _sceneHeight, const int _sceneWidth);
	API ~Scene();

	bool API checkIfObjectExists(const int objectID);
	const bool API toggleLayer(const int zIndex, bool render);
	const void API addNewObjectToLayer(const int zIndex, Object* object, bool renderPhysics = false, bool alwaysDrawLayer = false);

	vector<Drawable*> API getAllDrawablesInScene();

	vector <Object*> API getAllObjectsInScene();
	vector <Object*> getAllObjectsInSceneRenderPhysics();

	Object API *getObject(const int objectID);

	int API getSceneID() { return sceneID; }

	/// @brief
	/// OnAttach is executed when a scene is "attached" to the current running context
	/// usually this is can be used to prime a level with relevant data before starting it.
	/// Must be implemented by a concrete implementation of a scene
	API virtual void onAttach() = 0;
	/// @brief
	/// Start is called when a scene is ready to execute its logic, this can be percieved as the "main loop" of a scene
	/// Must be implemented by a concrete implementation of a scene
	API virtual void start(bool playSound) = 0;
	/// @brief
	/// OnDetach is called when a scene is destroyed/closed and is responsible for cleanup
	/// Must be implemented by a concrete implementation of a scene
	API virtual void onDetach() = 0;

	/// @brief
	/// run is called in the main loop on the currentScene
	/// If any work needs to be done during a scene this is were to place it
	API virtual void onUpdate() = 0;

	void setSceneWidth(const int width) { sceneWidth = width; }
	int getSceneWidth() const { return sceneWidth; }

	void setSceneHeight(const int height) { sceneHeight = height; }
	int getSceneHeight() const { return sceneHeight; }
    
	void setObjectToFollow(Object* obj) { objectToFollow = obj; }

	/// @brief 
	/// Returns the id of the object to follow
	/// @return 
	/// If no ObjectToFollow will return -1
	int getObjectToFollowID() const 
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
	Object* getObjectToFollow() { return objectToFollow; };

	API void removeObjectFromScene(Object* obj);

	API map<int, Layer*> getLayers() const;

	API void createLayer(const int zIndex, bool renderPhysics = false, bool alwaysDrawLayer = false);

	EventDispatcher& getEventDispatcher() { return dispatcher; };

	API int getHighestLayerIndex();
	API int addLayerOnHighestZIndex(Layer *_layer);
	API void removeLayer(const int zIndex);


protected:
	EventDispatcher dispatcher;

	bool hasActivePopUp = false;
	bool paused = false;
private:
	const int sceneID = 0;
	map<int, Layer*> layers;


	Object *objectToFollow = nullptr;

	int sceneWidth = WINDOW_WIDTH;
	int sceneHeight = WINDOW_HEIGHT;
};
