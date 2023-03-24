#pragma once

#include "GBC/Core/Core.h"

namespace gbc
{
	using EventType = uint8_t;
	enum : EventType
	{
		EventType_None,

		EventType_WindowClose,
		EventType_WindowResize,
		EventType_WindowMove,
		EventType_WindowFocus,
		EventType_WindowMinimize,
		EventType_WindowMaximize, 
		EventType_WindowPathDrop,
		EventType_WindowFramebufferResize,
		EventType_WindowContentScale,
		EventType_WindowRefresh,

		EventType_KeyPress,
		EventType_KeyRepeat,
		EventType_KeyRelease,
		EventType_KeyCharType,

		EventType_MouseButtonPress,
		EventType_MouseButtonRelease,
		EventType_MouseMove,
		EventType_MouseScroll,
		EventType_MouseEnter,

		_EventType_Window_First = EventType_WindowClose, _EventType_Window_Last = EventType_WindowRefresh,
		_EventType_Key_First = EventType_KeyPress, _EventType_Key_Last = EventType_KeyCharType,
		_EventType_Mouse_First = EventType_MouseButtonPress, _EventType_Mouse_Last = EventType_MouseEnter,
		_EventType_First = _EventType_Window_First, _EventType_Last = _EventType_Mouse_Last,
	};

#define _GBC_EVENT_GET_STATIC_TYPE(type) static constexpr auto GetStaticType() noexcept -> EventType { return type; }

	class Event
	{
	protected:
		constexpr Event(EventType type) noexcept;
	public:
		constexpr auto GetType() const noexcept -> EventType;
		constexpr auto IsWindowEvent() const noexcept -> bool;
		constexpr auto IsKeyEvent() const noexcept -> bool;
		constexpr auto IsMouseEvent() const noexcept -> bool;
		constexpr auto IsHandled() const noexcept -> bool;
		constexpr auto Handle() noexcept -> void;
	public:
#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const = 0;
#endif
	public:
		template<typename... Args>
		auto Dispatch(auto(*callback)(Event&, Args...) -> void, auto&&... args) -> void;

		template<typename Class, typename... Args>
		auto Dispatch(Class* object, auto(Class::*callback)(Event&, Args...) -> void, auto&&... args) -> void;
		
		template<typename EventSubclass, typename... Args>
		requires(std::is_base_of_v<Event, EventSubclass>)
		auto Dispatch(auto(*callback)(EventSubclass&, Args...) -> void, auto&&... args) -> void;

		template<typename Class, typename EventSubclass, typename... Args>
		requires(std::is_base_of_v<Event, EventSubclass>)
		auto Dispatch(Class* object, auto(Class::*callback)(EventSubclass&, Args...) -> void, auto&&... args) -> void;
	private:
		friend class Application;
	private:
		EventType m_Type : 5 {EventType_None};
		bool m_Handled : 1 {false};
	};
}

#include "Event.inl"
