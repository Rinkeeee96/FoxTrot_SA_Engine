#pragma once
#include "Scene.h"

namespace Glitch {
	using namespace std;
	/// @brief 
	/// Contains all scenes. Manages all scenes and objects. All calls from engine containing object movements should be handled in the scene manager. 
	class GLITCH_API SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		// Scene modifiers
		void createNewScene(const int sceneID);
		void setCurrentScene(const int sceneID);
		Scene* getSceneWithID(const int sceneID);

		// Object Modifiers
		void moveObject(const int ObjectID, const int X, const int Y);
		void moveObjectRelative(const int ObjectID, const int moveXby, const int moveYby);
		void rotateObject(const int ObjectID, const int rotation);
		void setObjectScale(const int ObjectID, const int scale);
		void setObjectDirection(const int ObjectID, const int dir);
		void setObjectStatic(const int ObjectID, const bool stat);

		// Pointer
		vector <Object*> pointerToCurrentObjectVector;

	protected:


	private:

		// Helper Functions
		bool checkIfSceneExists(const int);

		Scene* currentScene = nullptr;
		vector<Scene*> scenes = {};//vector<Scene*>();
	};
}
