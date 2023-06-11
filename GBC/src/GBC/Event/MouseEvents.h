#pragma once

#include "GBC/Event/Event.h"
#include "GBC/Core/Modifiers.h"
#include "GBC/Core/MouseButtons.h"

namespace gbc
{
	class MouseButtonPressEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::MouseButtonPress);

		constexpr MouseButtonPressEvent(MouseButton button, Modifiers modifiers)
			: Event{GetStaticType()}, m_Button{button}, m_Modifiers{modifiers} {}

		constexpr auto GetButton() const noexcept -> MouseButton { return m_Button; }
		constexpr auto GetModifiers() const noexcept -> Modifiers { return m_Modifiers; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		MouseButton m_Button : MouseButton::BitCount;
		Modifiers m_Modifiers;
	};

	class MouseButtonReleaseEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::MouseButtonRelease);

		constexpr MouseButtonReleaseEvent(MouseButton button, Modifiers modifiers)
			: Event{GetStaticType()}, m_Button{button}, m_Modifiers{modifiers} {}

		constexpr auto GetButton() const noexcept -> MouseButton { return m_Button; }
		constexpr auto GetModifiers() const noexcept -> Modifiers { return m_Modifiers; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		MouseButton m_Button : MouseButton::BitCount;
		Modifiers m_Modifiers;
	};

	class MouseMoveEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::MouseMove);

		constexpr MouseMoveEvent(float mousePosX, float mousePosY)
			: Event{GetStaticType()}, m_MousePosX{mousePosX}, m_MousePosY{mousePosY} {}

		constexpr auto GetMouseX() const noexcept -> float { return m_MousePosX; }
		constexpr auto GetMouseY() const noexcept -> float { return m_MousePosY; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		float m_MousePosX;
		float m_MousePosY;
	};

	class MouseScrollEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::MouseScroll);

		constexpr MouseScrollEvent(float scrollOffsetX, float scrollOffsetY)
			: Event{GetStaticType()}, m_ScrollOffsetX{scrollOffsetX}, m_ScrollOffsetY{scrollOffsetY} {}

		constexpr auto GetScrollOffsetX() const noexcept -> float { return m_ScrollOffsetX; }
		constexpr auto GetScrollOffsetY() const noexcept -> float { return m_ScrollOffsetY; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		float m_ScrollOffsetX;
		float m_ScrollOffsetY;
	};

	class MouseEnterEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::MouseEnter);

		constexpr MouseEnterEvent(bool entered)
			: Event{GetStaticType()}, m_Entered{entered} {}

		constexpr auto HasEntered() const noexcept -> bool { return m_Entered; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		bool m_Entered : 1;
	};
}
