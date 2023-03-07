#pragma once

#include "GBC/Event/Event.h"
#include "GBC/Event/Modifiers.h"
#include "GBC/Core/MouseButtons.h"

namespace gbc
{
	class MouseButtonPressEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::MouseButtonPress);

		constexpr MouseButtonPressEvent(MouseButton button, Modifiers modifiers, bool applicationOnly = false)
			: Event{GetStaticType(), applicationOnly}, m_Button{button}, m_Modifiers{modifiers} {}

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
		_GBC_EVENT_GET_STATIC_TYPE(EventType::MouseButtonRelease);

		constexpr MouseButtonReleaseEvent(MouseButton button, Modifiers modifiers, bool applicationOnly = false)
			: Event{GetStaticType(), applicationOnly}, m_Button{button}, m_Modifiers{modifiers} {}

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
		_GBC_EVENT_GET_STATIC_TYPE(EventType::MouseMove);

		constexpr MouseMoveEvent(float x, float y, bool applicationOnly = false)
			: Event{GetStaticType(), applicationOnly}, m_X{x}, m_Y{y} {}

		constexpr auto GetX() const noexcept -> float { return m_X; }
		constexpr auto GetY() const noexcept -> float { return m_Y; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		float m_X;
		float m_Y;
	};

	class MouseScrollEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::MouseScroll);

		constexpr MouseScrollEvent(float offsetX, float offsetY, bool applicationOnly = false)
			: Event{GetStaticType(), applicationOnly}, m_OffsetX{offsetX}, m_OffsetY{offsetY} {}

		constexpr auto GetOffsetX() const noexcept -> float { return m_OffsetX; }
		constexpr auto GetOffsetY() const noexcept -> float { return m_OffsetY; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		float m_OffsetX;
		float m_OffsetY;
	};

	class MouseEnterEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::MouseEnter);

		constexpr MouseEnterEvent(bool entered, bool applicationOnly = false)
			: Event{GetStaticType(), applicationOnly}, m_Entered{entered} {}

		constexpr auto HasEntered() const noexcept -> bool { return m_Entered; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		bool m_Entered;
	};
}
