#pragma once
#include "glpch.h"
#include "Glitch/Events/Event.h"

namespace Glitch {
	using EventCallbackFn = std::function<void(Event&)>;
	/// @brief 
	/// Struct for windowproperties, can be passed around to get data from the window
	struct WindowProps
	{
		int Id;
		const char* Title;
		unsigned int Width;
		unsigned int Height;
		bool vSync;
		EventCallbackFn EventCallback;

		WindowProps(
			const char* title = "Glitch engine",
			unsigned int width = 1280,
			unsigned int height = 720
		) : Title{ title }, Width{ width }, Height{ height }
		{
			vSync = false;
			Id = 0;
		}
	};

}