#include "gbcpch.h"
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
		stream << "WindowFramebufferResizeEvent: framebufferWidth=" << m_FramebufferWidth << " framebufferHeight=" << m_FramebufferHeight;
		return stream.str();
	}

	std::string WindowMoveEvent::ToString() const
	{
		std::stringstream stream;
		stream << "WindowMoveEvent: x=" << m_WindowPosX << " y=" << m_WindowPosY;
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
		stream << "WindowPathDropEvent: pathCount=" << m_Paths.size() << " paths=[";
		for (auto& path : m_Paths)
			stream << " \"" << path << '"';
		stream << ']';
		return stream.str();
	}

	std::string WindowContentScaleEvent::ToString() const
	{
		std::stringstream stream;
		stream << "WindowContentScaleEvent: contentScaleX=" << m_ContentScaleX << " contentScaleY=" << m_ContentScaleY;
		return stream.str();
	}

	std::string WindowRefreshEvent::ToString() const
	{
		return "WindowRefreshEvent";
	}
}

#endif
