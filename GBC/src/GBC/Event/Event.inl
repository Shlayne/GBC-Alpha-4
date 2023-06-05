#include "Event.h"

namespace gbc
{
	constexpr Event::Event(EventType type) noexcept
		: m_Type{type}
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(EventType, type);
	}

	constexpr auto Event::GetType() const noexcept -> EventType
	{
		return m_Type;
	}

	constexpr auto Event::IsWindowEvent() const noexcept -> bool
	{
		return EventType::WindowClose <= m_Type && m_Type <= EventType::WindowRefresh;
	}

	constexpr auto Event::IsKeyEvent() const noexcept -> bool
	{
		return EventType::KeyPress <= m_Type && m_Type <= EventType::KeyCharType;
	}

	constexpr auto Event::IsMouseEvent() const noexcept -> bool
	{
		return EventType::MouseButtonPress <= m_Type && m_Type <= EventType::MouseEnter;
	}

	constexpr auto Event::IsHandled() const noexcept -> bool
	{
		return m_Handled;
	}

	constexpr auto Event::Handle() noexcept -> void
	{
		m_Handled = true;
	}
	
	template<typename... Args>
	auto Event::Dispatch(auto(*callback)(Event&, Args...) -> void, auto&&... args) -> void
	{
		if (!m_Handled)
			callback(*this, std::forward<Args>(args)...);
	}
	
	template<typename Class, typename... Args>
	auto Event::Dispatch(Class* object, auto(Class::*callback)(Event&, Args...) -> void, auto&&... args) -> void
	{
		if (!m_Handled)
			(object->*callback)(*this, std::forward<Args>(args)...);
	}
	
	template<typename EventSubclass, typename... Args>
	requires(std::is_base_of_v<Event, EventSubclass>)
	auto Event::Dispatch(auto(*callback)(EventSubclass&, Args...) -> void, auto&&... args) -> void
	{
		if (!m_Handled && m_Type == EventSubclass::GetStaticType())
			callback(static_cast<EventSubclass&>(*this), std::forward<Args>(args)...);
	}
	
	template<typename Class, typename EventSubclass, typename... Args>
	requires(std::is_base_of_v<Event, EventSubclass>)
	auto Event::Dispatch(Class* object, auto(Class::*callback)(EventSubclass&, Args...) -> void, auto&&... args) -> void
	{
		if (!m_Handled && m_Type == EventSubclass::GetStaticType())
			(object->*callback)(static_cast<EventSubclass&>(*this), std::forward<Args>(args)...);
	}
}
