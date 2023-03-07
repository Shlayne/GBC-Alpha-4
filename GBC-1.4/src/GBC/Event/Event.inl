#include "Event.h"

namespace gbc
{
	constexpr Event::Event(EventType type, bool applicationOnly) noexcept
		: m_Type{type}
		, m_ApplicationOnly{applicationOnly}
	{

	}

	constexpr auto Event::GetType() const noexcept -> EventType
	{
		return m_Type;
	}

	constexpr auto Event::IsHandled() const noexcept -> bool
	{
		return m_Handled;
	}

	constexpr auto Event::Handle() noexcept -> void
	{
		m_Handled = true;
	}

	constexpr auto Event::IsApplicationOnly() const noexcept -> bool
	{
		return m_ApplicationOnly;
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
