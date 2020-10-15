#include "glpch.h"
#include "Application.h"
namespace Glitch {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
	/// @brief Constructor
	Application::Application()
	{
		sdlFacade = new SDL2Facade();
		renderer = new Renderer2d(sdlFacade);

		m_window = std::unique_ptr<Window>(Window::Create());

		m_window->SetFacade(sdlFacade);
		m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_window->Init();
		renderer->Init(&sceneManager.pointerToCurrentObjectVector);
		physics.Init(&sceneManager.pointerToCurrentObjectVector);
	}

	/// @brief Destructor
	Application::~Application() {}

	/// @brief Run
	/// The main of the application. Calls all the subsystems OnUpdate in order
	///		Window
	///		Renderer
	///		Physics
	void Application::Run() {
		while (isRunning)
		{
			m_window->OnUpdate();
			physics.update30();
			renderer->OnUpdate();
			// etc. OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		isRunning = false;
		m_window->Shutdown();
		renderer->Shutdown();
		return true;
	}

	/// @brief
	/// OnEvent handle an event specified within this method. Event can be on any eventType
	/// @param event 
	/// Abstract event can be of any type
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		GL_INFO(e.ToString());
	}
}