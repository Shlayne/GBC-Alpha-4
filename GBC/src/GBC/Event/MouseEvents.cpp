#include "gbcpch.h"
#if GBC_ENABLE_LOGGING
#include "MouseEvents.h"

namespace gbc
{
	std::string MouseButtonPressEvent::ToString() const
	{
		std::stringstream stream;
		stream << "MouseButtonPressEvent: button=" << static_cast<uint16_t>(m_Button) << " modifiers=" << +m_Modifiers;
		return stream.str();
	}

	std::string MouseButtonReleaseEvent::ToString() const
	{
		std::stringstream stream;
		stream << "MouseButtonReleaseEvent: button=" << static_cast<uint16_t>(m_Button) << " modifiers=" << +m_Modifiers;
		return stream.str();
	}

	std::string MouseMoveEvent::ToString() const
	{
		std::stringstream stream;
		stream << "MouseMoveEvent: x=" << m_X << " y=" << m_Y;
		return stream.str();
	}

	std::string MouseScrollEvent::ToString() const
	{
		std::stringstream stream;
		stream << "MouseScrollEvent: offsetX=" << m_OffsetX << " offsetY=" << m_OffsetY;
		return stream.str();
	}

	std::string MouseEnterEvent::ToString() const
	{
		std::stringstream stream;
		stream << "MouseEnterEvent: entered=" << m_Entered;
		return stream.str();
	}
}

#endif
