#pragma once

#include "GBC/Core/Core.h"
#include <functional>

namespace gbc
{
	GBC_DEFINE_BOUNDED_ENUM(
		EventType, uint8_t,

		// Window Events
		WindowClose,
		WindowResize,
		WindowMove,
		WindowFocus,
		WindowMinimize,
		WindowMaximize,
		WindowPathDrop,
		WindowFramebufferResize,
		WindowContentScale,
		WindowRefresh,

		// Key Events
		KeyPress,
		KeyRepeat,
		KeyRelease,
		KeyCharType,

		// Mouse Events
		MouseButtonPress,
		MouseButtonRelease,
		MouseMove,
		MouseScroll,
		MouseEnter
	);

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
		EventType m_Type : EventType::BitCount {};
		bool m_Handled : 1 {};
	};

	class Window;
	using EventCallback = std::function<auto(Event&, Window*) -> void>;
}

#include "Event.inl"
