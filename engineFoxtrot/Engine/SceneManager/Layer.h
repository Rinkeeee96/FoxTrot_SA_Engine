#pragma once
#include "Objects/Object.h"

class Layer
{
public:
	Layer() {};
	~Layer() {};

	void setVisible(bool value) { visible = value; }
	bool getVisible() const { return visible; }

	void setRender(bool value) { render = value; }
	bool getRender() const { return render; }

	void setAlwaysVisible(bool value) { alwaysVisible = value; }
	bool getAlwaysVisible() const { return alwaysVisible; }

	void setRenderPhysics(bool value) { renderPhysics = value; }
	bool getRenderPhysics() const { return renderPhysics; }

	map<int, Object*> getObjectsInLayer() { return objects; }
	Object* getSpecificObjectInLayer(int objectID) { return objects[objectID]; }
	void addObjectToLayer(int objectID, Object* obj) { objects[objectID] = obj; }

	bool objectExists(int objectID) {
		if (objects.find(objectID) != objects.end()) {
			return true;
		}
		return false;
	}

	void removeObject(int objectID) { objects.erase(objectID); }
	void clearObjects() { objects.clear(); }


protected:

private:
	bool visible = true;
	bool render = false;
	bool alwaysVisible = false;
	bool renderPhysics = false;
	// TODO clear on scene detach in destructor
	map<int, Object*> objects;

};