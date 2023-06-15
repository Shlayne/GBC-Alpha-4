#pragma once

#include "GBC/Event/Event.h"
#include <vector>
#include <string>

namespace gbc
{
	class WindowCloseEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowClose);

		constexpr WindowCloseEvent()
			: Event{GetStaticType()} {}

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	};

	class WindowResizeEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowResize);

		constexpr WindowResizeEvent(uint32_t width, uint32_t height)
			: Event{GetStaticType()}, m_Width{width}, m_Height{height} {}

		constexpr auto GetWidth() const noexcept -> uint32_t { return m_Width; }
		constexpr auto GetHeight() const noexcept -> uint32_t { return m_Height; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

	class WindowFramebufferResizeEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowFramebufferResize);

		constexpr WindowFramebufferResizeEvent(uint32_t framebufferWidth, uint32_t framebufferHeight)
			: Event{GetStaticType()}, m_FramebufferWidth{framebufferWidth}, m_FramebufferHeight{framebufferHeight} {}

		constexpr auto GetFramebufferWidth() const noexcept -> uint32_t { return m_FramebufferWidth; }
		constexpr auto GetFramebufferHeight() const noexcept -> uint32_t { return m_FramebufferHeight; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		uint32_t m_FramebufferWidth;
		uint32_t m_FramebufferHeight;
	};

	class WindowMoveEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowMove);

		constexpr WindowMoveEvent(int32_t windowPosX, int32_t windowPosY)
			: Event{GetStaticType()}, m_WindowPosX{windowPosX}, m_WindowPosY{windowPosY} {}

		constexpr auto GetWindowX() const noexcept -> int32_t { return m_WindowPosX; }
		constexpr auto GetWindowY() const noexcept -> int32_t { return m_WindowPosY; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		int32_t m_WindowPosX;
		int32_t m_WindowPosY;
	};

	class WindowFocusEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowFocus);

		constexpr WindowFocusEvent(bool focused)
			: Event{GetStaticType()}, m_Focused{focused} {}

		constexpr auto IsFocused() const noexcept -> bool { return m_Focused; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		bool m_Focused : 1;
	};

	class WindowMinimizeEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowMinimize);

		constexpr WindowMinimizeEvent(bool minimized)
			: Event{GetStaticType()}, m_Minimized{minimized} {}

		constexpr auto IsMinimized() const noexcept -> bool { return m_Minimized; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		bool m_Minimized : 1;
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowMaximize);

		constexpr WindowMaximizeEvent(bool maximized)
			: Event{GetStaticType()}, m_Maximized{maximized} {}

		constexpr auto IsMaximized() const noexcept -> bool { return m_Maximized; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		bool m_Maximized : 1;
	};

	class WindowPathDropEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowPathDrop);

		constexpr WindowPathDropEvent(uint32_t pathCount, const char** paths)
			: Event{GetStaticType()}
		{
			for (uint32_t i{}; i < pathCount; ++i)
				m_Paths.emplace_back(paths[i]);
		}

		constexpr auto GetPathCount() const noexcept -> size_t { return m_Paths.size(); }
		constexpr auto GetPaths() const noexcept -> const std::vector<std::string>& { return m_Paths; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		std::vector<std::string> m_Paths;
	};
	

	class WindowContentScaleEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowContentScale);

		constexpr WindowContentScaleEvent(float contentScaleX, float contentScaleY)
			: Event{GetStaticType()}, m_ContentScaleX{contentScaleX}, m_ContentScaleY{contentScaleY} {}

		constexpr auto GetContentScaleX() const noexcept -> float { return m_ContentScaleX; }
		constexpr auto GetContentScaleY() const noexcept -> float { return m_ContentScaleY; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		float m_ContentScaleX;
		float m_ContentScaleY;
	};

	class WindowRefreshEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowRefresh);

		constexpr WindowRefreshEvent()
			: Event{GetStaticType()} {}

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	};
}
