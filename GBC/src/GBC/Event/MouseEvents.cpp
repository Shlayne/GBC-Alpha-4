#include "gbcpch.h"
#if GBC_ENABLE_LOGGING
#include "MouseEvents.h"

namespace gbc
{
	std::string MouseButtonPressEvent::ToString() const
	{
		std::stringstream stream;
		stream << "MouseButtonPressEvent: button=" << +m_Button << " modifiers=" << +m_Modifiers;
		return stream.str();
	}

	std::string MouseButtonReleaseEvent::ToString() const
	{
		std::stringstream stream;
		stream << "MouseButtonReleaseEvent: button=" << +m_Button << " modifiers=" << +m_Modifiers;
		return stream.str();
	}

	std::string MouseMoveEvent::ToString() const
	{
		std::stringstream stream;
		stream << "MouseMoveEvent: mouseX=" << m_MousePos.x << " mouseY=" << m_MousePos.y;
		return stream.str();
	}

	std::string MouseScrollEvent::ToString() const
	{
		std::stringstream stream;
		stream << "MouseScrollEvent: scrollOffsetX=" << m_ScrollOffset.x << " scrollOffsetY=" << m_ScrollOffset.y;
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
