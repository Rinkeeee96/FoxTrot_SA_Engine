#pragma once
#include "Objects/Object.h"

/// @brief Class for a layer in scene
/// This contains all the objects in the layer
class Layer
{
public:
	Layer() {};
	~Layer() { clearObjects(); };

	API void setVisible(bool value) { visible = value; }
	API bool getVisible() const { return visible; }

	API void setRender(bool value) { render = value; }
	API bool getRender() const { return render; }

	API void setAlwaysVisible(bool value) { alwaysVisible = value; }
	API bool getAlwaysVisible() const { return alwaysVisible; }

	API void setRenderPhysics(bool value) { renderPhysics = value; }
	API bool getRenderPhysics() const { return renderPhysics; }

	//In here for the not friend classes who might need the objects in a layer
	API map<int, shared_ptr<Object>> getObjectsInLayer() { return objects; }
	API shared_ptr<Object> getSpecificObjectInLayer(int objectID) {
		if (objects.count(objectID) == 0) throw exception("Layer: object does not exist");
		return objects[objectID]; 
	}
	API void addObjectInLayer(shared_ptr<Object> obj) { objects[obj->getObjectId()] = shared_ptr<Object>(obj); }

	/// @brief Checks if object exists in the layer
	/// @param objectID 
	/// @return 
	API bool objectExists(int objectID) {
		if (objects.find(objectID) != objects.end()) {
			return true;
		}
		return false;
	}

	API void removeObject(int objectID) { 
		if (objects.count(objectID) == 0) throw exception("Layer: object does not exist");
		objects.erase(objectID); 
	}
	API void clearObjects() { objects.clear(); }

	/// @brief Optional method to override which is called when before a layer is loaded
	/// by a scene
	API virtual void onAttach() {}
	/// @brief Optional method to override which is called when before a layer is unloaded
	/// by a scene 
	API virtual void onDetach() {}


protected:
	// TODO clear on scene detach in destructor
	map<int, shared_ptr<Object>> objects;

private:
	bool visible = true;
	bool render = false;
	bool alwaysVisible = false;
	bool renderPhysics = false;

	friend class Scene;
	friend class VideoEngine;
};
