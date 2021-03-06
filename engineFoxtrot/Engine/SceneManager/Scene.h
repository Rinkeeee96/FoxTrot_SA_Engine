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
	const void API addNewObjectToLayer(const int zIndex, shared_ptr<Object> object, bool renderPhysics = false, bool alwaysDrawLayer = false);

	vector<shared_ptr<Drawable>> API getAllDrawablesInScene();

	vector <shared_ptr<Object>> API getAllObjectsInScene();
	vector <shared_ptr<Object>> API getAllObjectsInSceneRenderPhysics();

	shared_ptr<Object> API getObject(const int objectID);

	int API getSceneID() { return sceneID; }


	API virtual void onAttach() = 0;
	API virtual void start(bool playSound) = 0;
	API virtual void onDetach() = 0;
	API virtual void onUpdate(float deltaTime) = 0;

	void setSceneWidth(const int width) { sceneWidth = width; }
	int getSceneWidth() const { return sceneWidth; }

	void setSceneHeight(const int height) { sceneHeight = height; }
	int getSceneHeight() const { return sceneHeight; }
    
	void setObjectToFollow(shared_ptr<Object> obj) { objectToFollow = obj; }


	int getObjectToFollowID() const;
	shared_ptr<Object> getObjectToFollow() { return objectToFollow; };

	API void removeObjectFromScene(shared_ptr<Drawable> obj);
	API void removeObjectFromScene(shared_ptr<Object> obj);

	API map<int, shared_ptr<Layer>> getLayers() const;

	API void createLayer(const int zIndex, bool renderPhysics = false, bool alwaysDrawLayer = false);

	EventDispatcher& getEventDispatcher() { return dispatcher; };

	API int getHighestLayerIndex();
	API int addLayerOnHighestZIndex(shared_ptr<Layer> _layer);
	API void addLayerOnZIndex(const int zIndex, shared_ptr<Layer> _layer);
	API void removeLayer(const int zIndex);


protected:
	EventDispatcher dispatcher;

	bool hasActivePopUp = false;
	bool paused = false;
	map<int, shared_ptr<Layer>> layers;
private:
	const int sceneID = 0;


	shared_ptr<Object> objectToFollow = nullptr;

	int sceneWidth = WINDOW_WIDTH;
	int sceneHeight = WINDOW_HEIGHT;
};
