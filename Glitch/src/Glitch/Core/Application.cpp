#include "glpch.h"
#include "Application.h"
namespace Glitch {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		sdlFacade = new SDL2Facade();
		particleEmitter = new ParticleEmitter();
		renderer = new Renderer2d(sdlFacade, particleEmitter);

		m_window = std::unique_ptr<Window>(Window::Create());

		m_window->SetFacade(sdlFacade);
		m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_window->Init();
		renderer->Init(&sceneManager.pointerToCurrentObjectVector);
		physics.Init(&sceneManager.pointerToCurrentObjectVector);
	}

	Application::~Application() {}

	void Application::Run() {
		while (isRunning)
		{
			m_window->OnUpdate();
			physics.update30();
			particleEmitter->onUpdate();
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

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		GL_INFO(e.ToString());
	}
}