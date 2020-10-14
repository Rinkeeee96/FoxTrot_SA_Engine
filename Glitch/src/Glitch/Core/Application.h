#pragma once
#include "Core.h"
#include "Glitch/Renderer/window.h"
#include <Glitch\SceneManager\SceneManager.h>
#include <Glitch\Renderer\Renderer2d.h>
#include <Glitch\Physics\PhysicsEngine.h>
#include <Glitch\FPS\FrameData.h>
#include <Glitch\Events\\KeyEvent.h>

namespace Glitch {
	class GLITCH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	protected:
		FrameData* frameData;

		ISDL2Facade* sdlFacade;
		PhysicsEngine physics;
		
		SceneManager sceneManager;
		Renderer2d* renderer;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		std::unique_ptr<Window> m_window;
		bool isRunning = true;
	};
	// to be defined in Game/Client
	Application* CreateApplication(); 
}


