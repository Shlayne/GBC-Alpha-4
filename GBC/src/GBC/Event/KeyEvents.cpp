#include "gbcpch.h"
#if GBC_ENABLE_LOGGING
#include "KeyEvents.h"

namespace gbc
{
	std::string KeyPressEvent::ToString() const
	{
		std::stringstream stream;
		stream << "KeyPressEvent: keycode=" << static_cast<uint16_t>(m_Keycode) << " modifiers=" << +m_Modifiers;
		return stream.str();
	}

	std::string KeyRepeatEvent::ToString() const
	{
		std::stringstream stream;
		stream << "KeyRepeatEvent: keycode=" << static_cast<uint16_t>(m_Keycode) << " modifiers=" << +m_Modifiers;
		return stream.str();
	}

	std::string KeyReleaseEvent::ToString() const
	{
		std::stringstream stream;
		stream << "KeyReleaseEvent: keycode=" << static_cast<uint16_t>(m_Keycode) << " modifiers=" << +m_Modifiers;
		return stream.str();
	}

	std::string KeyCharTypeEvent::ToString() const
	{
		std::stringstream stream;
		stream << "KeyCharTypeEvent: codepoint=" << static_cast<uint32_t>(m_Codepoint);
		return stream.str();
	}
}

#endif
