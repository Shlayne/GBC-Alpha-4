#include "gbcpch.h"
#if GBC_ENABLE_LOGGING
#include "KeyEvents.h"

namespace gbc
{
	std::string KeyPressEvent::ToString() const
	{
		std::stringstream stream;
		stream << "KeyPressEvent: keycode=" << +m_Keycode << " modifiers=" << +m_Modifiers;
		return stream.str();
	}

	std::string KeyRepeatEvent::ToString() const
	{
		std::stringstream stream;
		stream << "KeyRepeatEvent: keycode=" << +m_Keycode << " modifiers=" << +m_Modifiers;
		return stream.str();
	}

	std::string KeyReleaseEvent::ToString() const
	{
		std::stringstream stream;
		stream << "KeyReleaseEvent: keycode=" << +m_Keycode << " modifiers=" << +m_Modifiers;
		return stream.str();
	}

	std::string KeyCharTypeEvent::ToString() const
	{
		std::stringstream stream;
		stream << "KeyCharTypeEvent: codepoint=" << m_Codepoint;
		return stream.str();
	}
}

#endif
