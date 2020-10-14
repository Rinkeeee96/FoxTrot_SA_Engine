#pragma once
#include "Event.h"

namespace Glitch {
	/// @brief
	/// WindowResizedEvent is fired when the window is resized. Derived class of event. 
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		/// @brief
		/// Returns the Width of the resized window
		unsigned int GetWidth() const { return m_Width; }
		/// @brief
		/// Returns the Height of the resized window
		unsigned int GetHeight() const { return m_Height; }

		/// @brief
		/// Returns "WindowResizeEvent: + widht + height"
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	/// @brief
	/// WindowClosedEvent is fired when the window is closed. Derived class of event. 
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// @brief
	/// AppTickEvent is fired when a tick happened in the engine. Derived class of event. 
	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// @brief
	/// AppUpdateEvent is fired when a the engine updated something. Derived class of event. 
	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// @brief
	/// AppRenderEvent is fired when a render event has happened. Derived class of event. 
	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}