#pragma once
#include "glpch.h"
#include "Glitch/Core/Core.h"

namespace Glitch {
	// events zijn nu blocking, zodra er een event wordt afgevuurd stopt de main code
	// en processed de engine het event, in de toekomst framebuffer toevoegen voor events
	
	/// @brief
	/// EventType enum all the derived event types that can be fired as an enum
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		
		Engine30, Engine60
	};

	/// @brief
	/// EventCategory catagorizes any event in this enum
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/// @brief
	/// Abstract event class. Multiple events have this class as a super class
	class Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;
		/// @brief
		/// Returns the eventType of a specific event
		/// @return EventType
		virtual EventType GetEventType() const = 0;
		/// @brief
		/// Returns the name of a specific event
		virtual const char* GetName() const = 0;
		/// @brief
		/// Returns the category of a specific event
		/// @return EventCatagory enum as int
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		/// @brief
		/// Checks wheter the event is in the eventCategory
		/// @param category
		/// EventCategory enum
		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	/// @brief
	/// Event dispatcher responsible for dispatching events to the corresponding classes that listen to these events
	class EventDispatcher
	{
	public:
		/// @brief Constructor
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}
		
		/// @brief
		/// Generic method. Dispatches the event to the corresponding classes
		/// @param func
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}