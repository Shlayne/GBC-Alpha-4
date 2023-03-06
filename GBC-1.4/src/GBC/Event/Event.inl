#include "Event.h"

namespace gbc
{
	constexpr Event::Event(EventType type) noexcept
		: m_Type{type}
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

	template<typename... Args>
	auto Event::Dispatch(auto(*callback)(Event&, Args...) -> void, Args&&... args)
	{
		if (!m_Handled)
			callback(*this, std::forward<Args>(args)...);
	}

	template<typename C, typename... Args>
	auto Event::Dispatch(C* object, auto(C::*callback)(Event&, Args...) -> void, Args&&... args)
	{
		if (!m_Handled)
			(object->*callback)(*this, std::forward<Args>(args)...);
	}

	template<typename E, typename... Args>
	requires(std::is_base_of_v<Event, E>)
	auto Event::Dispatch(auto(*callback)(E&, Args...) -> void, Args&&... args)
	{
		if (!m_Handled && m_Type == E::GetStaticType())
			callback(static_cast<E&>(*this), std::forward<Args>(args)...);
	}

	template<typename C, typename E, typename... Args>
	requires(std::is_base_of_v<Event, E>)
	auto Event::Dispatch(C* object, auto(C::*callback)(E&, Args...) -> void, Args&&... args)
	{
		if (!m_Handled && m_Type == E::GetStaticType())
			(object->*callback)(static_cast<E&>(*this), std::forward<Args>(args)...);
	}
}
