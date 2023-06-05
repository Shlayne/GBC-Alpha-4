#pragma once

#include "GBC/Event/Event.h"
#include <glm/glm.hpp>

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

		constexpr WindowResizeEvent(glm::ivec2 size)
			: Event{GetStaticType()}, m_Size{size} {}

		constexpr auto GetWidth() const noexcept -> int32_t { return m_Size.x; }
		constexpr auto GetHeight() const noexcept -> int32_t { return m_Size.y; }
		constexpr auto GetSize() const noexcept -> glm::ivec2 { return m_Size; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		glm::ivec2 m_Size;
	};

	class WindowFramebufferResizeEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowFramebufferResize);

		constexpr WindowFramebufferResizeEvent(glm::ivec2 framebufferSize)
			: Event{GetStaticType()}, m_FramebufferSize{framebufferSize} {}

		constexpr auto GetFramebufferWidth() const noexcept -> int32_t { return m_FramebufferSize.x; }
		constexpr auto GetFramebufferHeight() const noexcept -> int32_t { return m_FramebufferSize.y; }
		constexpr auto GetFramebufferSize() const noexcept -> glm::ivec2 { return m_FramebufferSize; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		glm::ivec2 m_FramebufferSize;
	};

	class WindowMoveEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowMove);

		constexpr WindowMoveEvent(glm::ivec2 windowPos)
			: Event{GetStaticType()}, m_WindowPos{windowPos} {}

		constexpr auto GetWindowX() const noexcept -> int32_t { return m_WindowPos.x; }
		constexpr auto GetWindowY() const noexcept -> int32_t { return m_WindowPos.y; }
		constexpr auto GetWindowPos() const noexcept -> glm::ivec2 { return m_WindowPos; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		glm::ivec2 m_WindowPos;
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
		bool m_Focused;
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
		bool m_Minimized;
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
		bool m_Maximized;
	};

	class WindowPathDropEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowPathDrop);

		constexpr WindowPathDropEvent(uint32_t pathCount, const char** paths)
			: Event{GetStaticType()}, m_PathCount{pathCount}, m_Paths{paths} {}

		constexpr auto GetPathCount() const noexcept -> uint32_t { return m_PathCount; }
		constexpr auto GetPaths() const noexcept -> const char* const* { return m_Paths; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		uint32_t m_PathCount;
		const char** m_Paths;
	};
	

	class WindowContentScaleEvent : public Event
	{
	public:
		_GBC_EVENT_GET_STATIC_TYPE(EventType::WindowContentScale);

		constexpr WindowContentScaleEvent(glm::vec2 contentScale)
			: Event{GetStaticType()}, m_ContentScale{contentScale} {}

		constexpr auto GetContentScaleX() const noexcept -> float { return m_ContentScale.x; }
		constexpr auto GetContentScaleY() const noexcept -> float { return m_ContentScale.y; }
		constexpr auto GetContentScale() const noexcept -> glm::vec2 { return m_ContentScale; }

#if GBC_ENABLE_LOGGING
		virtual std::string ToString() const override;
#endif
	private:
		glm::vec2 m_ContentScale;
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
