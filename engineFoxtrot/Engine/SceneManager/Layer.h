#pragma once
#include "Objects/Object.h"

class Layer
{
public:
	Layer() {};
	~Layer() {};

	API void setVisible(bool value) { visible = value; }
	API bool getVisible() const { return visible; }

	API void setRender(bool value) { render = value; }
	API bool getRender() const { return render; }

	API void setAlwaysVisible(bool value) { alwaysVisible = value; }
	API bool getAlwaysVisible() const { return alwaysVisible; }

	API void setRenderPhysics(bool value) { renderPhysics = value; }
	API bool getRenderPhysics() const { return renderPhysics; }

	API map<int, Object*> getObjectsInLayer() { return objects; }
	API Object* getSpecificObjectInLayer(int objectID) { return objects[objectID]; }
	API void addObjectToLayer(int objectID, Object* obj) { if(!objectExists(objectID))objects[objectID] = obj; }

	API bool objectExists(int objectID) {
		if (objects.find(objectID) != objects.end()) {
			return true;
		}
		return false;
	}

	API void removeObject(int objectID) { objects.erase(objectID); }
	API void clearObjects() { objects.clear(); }


protected:

private:
	bool visible = true;
	bool render = false;
	bool alwaysVisible = false;
	bool renderPhysics = false;
	// TODO clear on scene detach in destructor
	map<int, Object*> objects;

};