#pragma once
#include "Core.h"
#include "Glitch/Renderer/window.h"
#include <Glitch\SceneManager\SceneManager.h>
#include <Glitch\Renderer\Renderer2d.h>
#include <Glitch\Physics\PhysicsEngine.h>

namespace Glitch {

	/// @class 
	/// Application used as main entry point for the engine. Contains the main loop and all the subsystems
	class GLITCH_API Application
	{
	public:
		/// @brief Constructor
		Application();
		/// @brief Destructor
		virtual ~Application();

		/// @brief Run
		/// The main of the application. Calls all the subsystems OnUpdate in order
		///		Window
		///		Renderer
		///		Physics
		void Run();

		/// @brief
		/// OnEvent handle an event specified within this method. Event can be on any eventType
		/// @param Abstract event 
		void OnEvent(Event& e);
	protected:
		ISDL2Facade* sdlFacade;
		PhysicsEngine physics;
		
		SceneManager sceneManager;
		Renderer2d* renderer;

		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_window;
		bool isRunning = true;
	};
	// to be defined in Game/Client
	Application* CreateApplication(); 
}


