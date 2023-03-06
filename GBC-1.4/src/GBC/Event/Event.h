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
		KeyPress, KeyRepeat, KeyRelease, KeyChar,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll, MouseEnter,
	};

#define _GBC_EVENT_GET_STATIC_TYPE(type) static constexpr auto GetStaticType() noexcept -> EventType { return type; }

	class Event
	{
	protected:
		constexpr Event(EventType type) noexcept;
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
		auto Dispatch(auto(*callback)(Event&, Args...) -> void, Args&&... args);

		template<typename C, typename... Args>
		auto Dispatch(C* object, auto(C::*callback)(Event&, Args...) -> void, Args&&... args);

		template<typename E, typename... Args>
		requires(std::is_base_of_v<Event, E>)
		auto Dispatch(auto(*callback)(E&, Args...) -> void, Args&&... args);

		template<typename C, typename E, typename... Args>
		requires(std::is_base_of_v<Event, E>)
		auto Dispatch(C* object, auto(C::*callback)(E&, Args...) -> void, Args&&... args);
	private:
		EventType m_Type : 7 {EventType::None};
		bool m_Handled : 1 {false};
	};

#if GBC_ENABLE_LOGGING
	inline std::ostream& operator<<(std::ostream& ostream, const Event& event)
	{
		return ostream << event.ToString();
	}
#endif

	class Window;
	using EventCallback = std::function<void(Event&, Window&)>;
}

#include "Event.inl"
