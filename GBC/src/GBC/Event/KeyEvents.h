#pragma once

#include "GBC/Event/Event.h"
#include "GBC/Core/Modifiers.h"
#include "GBC/Core/Keycodes.h"

namespace gbc
{
	class KeyPressEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::KeyPress);

		constexpr KeyPressEvent(Keycode keycode, Modifiers modifiers) noexcept
			: Event{GetStaticType()}, m_Keycode{keycode}, m_Modifiers{modifiers} {}

		constexpr Keycode GetKeycode() const noexcept { return m_Keycode; }
		constexpr Modifiers GetModifiers() const noexcept { return m_Modifiers; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		Keycode m_Keycode;
		Modifiers m_Modifiers;
	};

	class KeyRepeatEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::KeyRepeat);

		constexpr KeyRepeatEvent(Keycode keycode, Modifiers modifiers) noexcept
			: Event{GetStaticType()}, m_Keycode{keycode}, m_Modifiers{modifiers} {}

		constexpr Keycode GetKeycode() const noexcept { return m_Keycode; }
		constexpr Modifiers GetModifiers() const noexcept { return m_Modifiers; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		Keycode m_Keycode;
		Modifiers m_Modifiers;
	};

	class KeyReleaseEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::KeyRelease);

		constexpr KeyReleaseEvent(Keycode keycode, Modifiers modifiers)
			: Event{GetStaticType()}, m_Keycode{keycode}, m_Modifiers{modifiers} {}

		constexpr Keycode GetKeycode() const noexcept { return m_Keycode; }
		constexpr Modifiers GetModifiers() const noexcept { return m_Modifiers; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		Keycode m_Keycode;
		Modifiers m_Modifiers;
	};

	class KeyCharTypeEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::KeyCharType);

		constexpr KeyCharTypeEvent(Codepoint codepoint)
			: Event{GetStaticType()}, m_Codepoint{codepoint} {}

		constexpr Codepoint GetCodepoint() const noexcept { return m_Codepoint; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		Codepoint m_Codepoint;
	};
}
