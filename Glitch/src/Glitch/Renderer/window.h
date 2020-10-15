#pragma once
#include "Glitch\Events\ApplicationEvent.h"
#include <Glitch\Facades\SDL2\SDL2Facade.h>
#include "Glitch/Renderer/WindowProps.h"
#include "Glitch/ISystem.h"
namespace Glitch {
	/// @brief 
	/// Abstract base class of a window. A window is platform specific, so for every platform a window base class should be created
	class GLITCH_API Window : public ISystem
	{
	public:
		virtual void SetFacade(ISDL2Facade* windowFacade) = 0;

		virtual ~Window() {};


		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVsync(bool enabled) = 0;
		virtual bool IsVsync() const = 0;

		virtual WindowProps* GetProperties() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

		// Inherited via ISystem
		virtual void OnUpdate() = 0;
		virtual void Init() = 0;
		virtual void Shutdown();
	};
}