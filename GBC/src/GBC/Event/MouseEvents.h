#pragma once

#include "GBC/Event/Event.h"
#include "GBC/Event/Modifiers.h"
#include "GBC/Core/MouseButtons.h"
#include <glm/glm.hpp>

namespace gbc
{
	class MouseButtonPressEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType_MouseButtonPress);

		constexpr MouseButtonPressEvent(MouseButton button, Modifiers modifiers)
			: Event{GetStaticType()}, m_Button{button}, m_Modifiers{modifiers} {}

		constexpr auto GetButton() const noexcept -> MouseButton { return m_Button; }
		constexpr auto GetModifiers() const noexcept -> Modifiers { return m_Modifiers; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		MouseButton m_Button;
		Modifiers m_Modifiers;
	};

	class MouseButtonReleaseEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType_MouseButtonRelease);

		constexpr MouseButtonReleaseEvent(MouseButton button, Modifiers modifiers)
			: Event{GetStaticType()}, m_Button{button}, m_Modifiers{modifiers} {}

		constexpr auto GetButton() const noexcept -> MouseButton { return m_Button; }
		constexpr auto GetModifiers() const noexcept -> Modifiers { return m_Modifiers; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		MouseButton m_Button;
		Modifiers m_Modifiers;
	};

	class MouseMoveEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType_MouseMove);

		constexpr MouseMoveEvent(glm::vec2 mousePos)
			: Event{GetStaticType()}, m_MousePos{mousePos} {}

		constexpr auto GetMouseX() const noexcept -> float { return m_MousePos.x; }
		constexpr auto GetMouseY() const noexcept -> float { return m_MousePos.y; }
		constexpr auto GetMousePos() const noexcept -> glm::vec2 { return m_MousePos; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		glm::vec2 m_MousePos;
	};

	class MouseScrollEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType_MouseScroll);

		constexpr MouseScrollEvent(glm::vec2 scrollOffset)
			: Event{GetStaticType()}, m_ScrollOffset{scrollOffset} {}

		constexpr auto GetScrollOffsetX() const noexcept -> float { return m_ScrollOffset.x; }
		constexpr auto GetScrollOffsetY() const noexcept -> float { return m_ScrollOffset.y; }
		constexpr auto GetScrollOffset() const noexcept -> glm::vec2 { return m_ScrollOffset; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		glm::vec2 m_ScrollOffset;
	};

	class MouseEnterEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType_MouseEnter);

		constexpr MouseEnterEvent(bool entered)
			: Event{GetStaticType()}, m_Entered{entered} {}

		constexpr auto HasEntered() const noexcept -> bool { return m_Entered; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		bool m_Entered;
	};
}
