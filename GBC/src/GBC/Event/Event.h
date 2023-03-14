#pragma once

#include "GBC/Core/Core.h"
#include <functional>

namespace gbc
{
	enum class EventType : uint8_t
	{
		None = 0,
		WindowClose, WindowResize, WindowMove, WindowFocus, WindowMinimize, WindowMaximize, 
			WindowPathDrop, WindowFramebufferResize, WindowContentScale, WindowRefresh,
		KeyPress, KeyRepeat, KeyRelease, KeyCharType,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll, MouseEnter,
	};

#define _GBC_EVENT_GET_STATIC_TYPE(type) static constexpr auto GetStaticType() noexcept -> EventType { return type; }

	class Event
	{
	protected:
		constexpr Event(EventType type, bool applicationOnly = false) noexcept;
	public:
		constexpr auto GetType() const noexcept -> EventType;
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
		constexpr auto IsApplicationOnly() const noexcept -> bool;
	private:
		EventType m_Type : 5 {EventType::None};
		bool m_Handled : 1 {false};
		bool m_ApplicationOnly : 1 {false};
	};

#if GBC_ENABLE_LOGGING
	inline std::ostream& operator<<(std::ostream& ostream, const Event& event)
	{
		return ostream << event.ToString();
	}
#endif
}

#include "Event.inl"
