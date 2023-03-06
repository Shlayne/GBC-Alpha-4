#include "GBC/Core/Core.h"
#if GBC_ENABLE_LOGGING
#include "WindowEvents.h"

namespace gbc
{
	std::string WindowCloseEvent::ToString() const
	{
		return "WindowCloseEvent";
	}

	std::string WindowResizeEvent::ToString() const
	{
		std::stringstream stream;
		stream << "WindowResizeEvent: width=" << m_Width << " height=" << m_Height;
		return stream.str();
	}

	std::string WindowFramebufferResizeEvent::ToString() const
	{
		std::stringstream stream;
		stream << "WindowFramebufferResizeEvent: width=" << m_Width << " height=" << m_Height;
		return stream.str();
	}

	std::string WindowMoveEvent::ToString() const
	{
		std::stringstream stream;
		stream << "WindowMoveEvent: x=" << m_X << " y=" << m_Y;
		return stream.str();
	}

	std::string WindowFocusEvent::ToString() const
	{
		std::stringstream stream;
		stream << "WindowFocusEvent: focused=" << m_Focused;
		return stream.str();
	}

	std::string WindowMinimizeEvent::ToString() const
	{
		std::stringstream stream;
		stream << "WindowMinimizeEvent: minimized=" << m_Minimized;
		return stream.str();
	}

	std::string WindowMaximizeEvent::ToString() const
	{
		std::stringstream stream;
		stream << "WindowMaximizeEvent: maximized=" << m_Maximized;
		return stream.str();
	}

	std::string WindowPathDropEvent::ToString() const
	{
		std::stringstream stream;
		stream << "WindowDropEvent: pathCount=" << m_PathCount << " paths:";
		for (uint32_t i = 0; i < m_PathCount; i++)
			stream << " \"" << m_Paths[i] << '"';
		return stream.str();
	}

	std::string WindowContentScaleEvent::ToString() const
	{
		std::stringstream stream;
		stream << "WindowContentScaleEvent: scaleX=" << m_ScaleX << " scaleY=" << m_ScaleY;
		return stream.str();
	}

	std::string WindowRefreshEvent::ToString() const
	{
		return "WindowContentScaleEvent";
	}
}

#endif
