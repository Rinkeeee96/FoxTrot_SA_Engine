#pragma once

#include "glpch.h"
#include "PhysicsFacade.h"
#include "Glitch/Core/Core.h"

namespace Glitch {
	class GLITCH_API PhysicsEngine
	{
	public:
		vector <Object*>* pointerToObjectVector = nullptr;

		PhysicsEngine();
		~PhysicsEngine();

		void registerObjectInCurrentVectorWithPhysicsEngine();

		void MoveLeft(const int objectId);
		void MoveRight(const int objectId);
		void Jump(const int objectId);
		void JumpLeft(const int objectId);
		void JumpRight(const int objectId);

		void update30();

		//Set to private after testing!!!
		IPhysicsFacade* physicsFacade = new PhysicsFacade;
	private:

		Object* getObject(const int objectId);
	};
}