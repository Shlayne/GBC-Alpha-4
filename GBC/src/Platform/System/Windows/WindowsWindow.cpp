#include "gbcpch.h"
#include "WindowsWindow.h"
#include "GBC/Event/Events.h"
#include "WindowsConversions.h"
#if GBC_CONFIG_DEBUG
	#include "GBC/Rendering/RendererAPI.h"
#endif

namespace gbc
{
	auto Window::CreateScope(const WindowInfo& info) -> Scope<Window>
	{
		return gbc::CreateScope<WindowsWindow>(info);
	}

	WindowsWindow::WindowsWindow(const WindowInfo& info)
		: m_Title{info.title}
		, m_VSync{!!info.vsync}
		, m_Resizable{!!info.resizable}
		, m_MouseCaptured{!!info.mouseCaptured}
		, m_Focused{!!info.focused}
		, m_Maximized{!!info.maximized}
		, m_WindowMode{info.windowMode}
	{
		// TODO: profile function

		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(WindowMode, m_WindowMode);

		// Set appropriate window hints.
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, m_Resizable);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, m_Focused);
		glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
#if GBC_CONFIG_DEBUG
		if (RendererAPI::GetType() == RendererAPI::OpenGL)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		// TODO: save which monitor the window was on last time it ran to a file.
		// Maybe this save file is a part of a profile, and people can have many.
		// Use that monitor if it exists, otherwise, use the primary monitor.
		GLFWmonitor* defaultMonitor{glfwGetPrimaryMonitor()};
		GLFWmonitor* fullscreenMonitor{};
		const GLFWvidmode* vidmode{};

		switch (m_WindowMode)
		{
		case WindowMode::Windowed:
			m_Current.size.x = info.width;
			m_Current.size.y = info.height;
			break;
		case WindowMode::Fullscreen:
			fullscreenMonitor = defaultMonitor;
			// Using [[fallthrough]] makes this not compile, but intellisense warns if it's not used.
		case WindowMode::BorderlessWindowed:
			m_Backup.size.x = info.width;
			m_Backup.size.y = info.height;
			vidmode = glfwGetVideoMode(defaultMonitor);
			m_Current.size.x = vidmode->width;
			m_Current.size.y = vidmode->height;
			break;
		}

		// Actually create the window.
		{
			// TODO: profile scope
			m_Handle = glfwCreateWindow(m_Current.size.x, m_Current.size.y, m_Title.c_str(), fullscreenMonitor, nullptr);
			GBC_CORE_ASSERT(m_Handle, "Failed to create GLFW window.");
		}

		int32_t left, top, right, bottom;
		glfwGetMonitorWorkarea(defaultMonitor, &left, &top, &right, &bottom);
		glm::ivec2 monitorWorkArea{right - left, bottom - top};
		glfwGetWindowFrameSize(m_Handle, &left, &top, &right, &bottom);
		// Windows 10 always returns left = top = bottom = 8 for bordered windows (it should be 1)
		glm::ivec2 windowFrameSize{right + left, bottom + top - 7};
		glm::ivec2 windowPosition{glm::ivec2{left, top} + (monitorWorkArea - (glm::ivec2{m_Current.size} + windowFrameSize)) / 2};

		if (m_WindowMode == WindowMode::Windowed)
			m_Current.position = windowPosition;
		else
			m_Backup.position = windowPosition;

		glfwSetWindowPos(m_Handle, m_Current.position.x, m_Current.position.y);
		glfwSetInputMode(m_Handle, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
		glfwSetWindowUserPointer(m_Handle, this);

		m_Context = Context::CreateScope({m_Handle});

		Impl_SetVSync(m_VSync);
		Impl_SetMouseCaptured(m_MouseCaptured);

		if (m_Maximized)
		{
			glfwMaximizeWindow(m_Handle);
			glfwGetWindowSize(m_Handle, reinterpret_cast<int32_t*>(&m_Current.size.x), reinterpret_cast<int32_t*>(&m_Current.size.y));
			glfwGetWindowPos(m_Handle, &m_Current.position.x, &m_Current.position.y);
		}

		glfwShowWindow(m_Handle);
		SetWindowCallbacks(m_Handle);
	}

	WindowsWindow::~WindowsWindow()
	{
		// TODO: profile function
		glfwDestroyWindow(m_Handle);
	}

	auto WindowsWindow::SetEventCallback(const EventCallback& callback) -> void
	{
		m_EventCallback = callback;
	}

	auto WindowsWindow::SwapBuffers() -> void
	{
		m_Context->SwapBuffers();
	}

	auto WindowsWindow::Close() -> void
	{
		m_ShouldClose = true;
	}

	auto WindowsWindow::ShouldClose() -> bool
	{
		return m_ShouldClose || glfwWindowShouldClose(m_Handle);
	}

	auto WindowsWindow::Impl_SetTitle(std::string_view title) -> void
	{
		glfwSetWindowTitle(m_Handle, title.data());
		m_Title = title;
	}

	auto WindowsWindow::Impl_SetVSync(bool enabled) -> void
	{
		glfwSwapInterval(enabled);
		m_VSync = enabled;
	}

	auto WindowsWindow::Impl_SetResizable(bool enabled) -> void
	{
		glfwSetWindowAttrib(m_Handle, GLFW_RESIZABLE, enabled);
		m_Resizable = enabled;
	}

	auto WindowsWindow::Impl_SetWindowMode(WindowMode windowMode) -> void
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(WindowMode, windowMode);

		bool decorated{};
		GLFWmonitor* monitor{};
		glm::ivec2 windowPos{0};
		glm::uvec2 windowSize{0};

		switch (windowMode)
		{
		case WindowMode::Windowed:
			windowPos = m_Backup.position;
			windowSize = m_Backup.size;
			decorated = true;
			break;
		case WindowMode::Fullscreen:
			if (m_WindowMode == WindowMode::Windowed)
				m_Backup = m_Current;
			GetWindowMonitor(monitor, windowPos, windowSize);
			break;
		case WindowMode::BorderlessWindowed:
			if (m_WindowMode == WindowMode::Windowed)
				m_Backup = m_Current;
			GetWindowMonitor(monitor, windowPos, windowSize);
			monitor = nullptr;
			break;
		}

		glfwSetWindowAttrib(m_Handle, GLFW_DECORATED, decorated);
		glfwSetWindowMonitor(m_Handle, monitor, windowPos.x, windowPos.y, windowSize.x, windowSize.y, GLFW_DONT_CARE);
		m_Current.position = windowPos;
		m_Current.size = windowSize;

		m_WindowMode = windowMode;
	}

	auto WindowsWindow::Impl_SetMouseCaptured(bool enabled) -> void
	{
		glfwSetInputMode(m_Handle, GLFW_CURSOR, enabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		m_MouseCaptured = enabled;
	}

	auto WindowsWindow::GetWindowMonitor(GLFWmonitor*& outMonitor, glm::ivec2& outMonitorPos, glm::uvec2& outMonitorSize) -> void
	{
		// From: https://stackoverflow.com/questions/21421074/how-to-create-a-full-screen-window-on-the-current-monitor-with-glfw
		// Get the monitor that most of the window is on. There is a Windows function for this, but it's not exposed via glfw :/
		int32_t largestOverlap{INT_MIN};

		int32_t monitorCount;
		GLFWmonitor** monitors{glfwGetMonitors(&monitorCount)};

		for (int32_t i{}; i < monitorCount; i++)
		{
			const GLFWvidmode* videoMode{glfwGetVideoMode(monitors[i])};

			int32_t monitorX, monitorY;
			glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);

			int32_t overlapX{std::max(0, std::min(m_Current.position.x + static_cast<int32_t>(m_Current.size.x), monitorX + videoMode->width) - std::max(m_Current.position.x, monitorX))};
			int32_t overlapY{std::max(0, std::min(m_Current.position.y + static_cast<int32_t>(m_Current.size.y), monitorY + videoMode->height) - std::max(m_Current.position.y, monitorY))};
			int32_t overlap{overlapX * overlapY};

			if (overlap > largestOverlap)
			{
				largestOverlap = overlap;
				outMonitor = monitors[i];
				outMonitorPos = {monitorX, monitorY};
				outMonitorSize = {static_cast<uint32_t>(videoMode->width), static_cast<uint32_t>(videoMode->height)};
			}
		}
	}

	auto WindowsWindow::SetWindowCallbacks(GLFWwindow* handle) -> void
	{
		// Window Events
		glfwSetWindowCloseCallback(handle, &WindowsWindow::WindowCloseCallback);
		glfwSetWindowSizeCallback(handle, &WindowsWindow::WindowSizeCallback);
		glfwSetFramebufferSizeCallback(handle, &WindowsWindow::FramebufferSizeCallback);
		glfwSetWindowPosCallback(handle, &WindowsWindow::WindowPosCallback);
		glfwSetWindowFocusCallback(handle, &WindowsWindow::WindowFocusCallback);
		glfwSetWindowIconifyCallback(handle, &WindowsWindow::WindowIconifyCallback);
		glfwSetWindowMaximizeCallback(handle, &WindowsWindow::WindowMaximizeCallback);
		glfwSetDropCallback(handle, &WindowsWindow::DropCallback);
		glfwSetWindowContentScaleCallback(handle, &WindowsWindow::WindowContentScaleCallback);
		glfwSetWindowRefreshCallback(handle, &WindowsWindow::WindowRefreshCallback);

		// Key Events
		glfwSetKeyCallback(handle, &WindowsWindow::KeyCallback);
		glfwSetCharCallback(handle, &WindowsWindow::CharCallback);

		// Mouse Events
		glfwSetMouseButtonCallback(handle, &WindowsWindow::MouseButtonCallback);
		glfwSetCursorPosCallback(handle, &WindowsWindow::CursorPosCallback);
		glfwSetScrollCallback(handle, &WindowsWindow::ScrollCallback);
		glfwSetCursorEnterCallback(handle, &WindowsWindow::CursorEnterCallback);
	}

	// Window Callbacks

	auto WindowsWindow::WindowCloseCallback(GLFWwindow* handle) -> void
	{
		// TODO: for now, assuming the user pointer is nonnull is fine.
		// However, if ImGui events are made to chain these callbacks,
		// then that will have to change, in addition to moving the
		// event callback to the Input class and having it be accessible
		// by any Window subclass, including WindowsWindow.
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		WindowCloseEvent event;
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowSizeCallback(GLFWwindow* handle, int width, int height) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		window.m_Current.size = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
		WindowResizeEvent event{window.m_Current.size.x, window.m_Current.size.y};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::FramebufferSizeCallback(GLFWwindow* handle, int width, int height) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		window.m_FramebufferWidth = static_cast<uint32_t>(width);
		window.m_FramebufferHeight = static_cast<uint32_t>(height);
		WindowFramebufferResizeEvent event{window.m_FramebufferWidth, window.m_FramebufferHeight};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowPosCallback(GLFWwindow* handle, int x, int y) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		window.m_Current.position = {static_cast<uint32_t>(x), static_cast<uint32_t>(y)};
		WindowMoveEvent event{window.m_Current.position.x, window.m_Current.position.y};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowFocusCallback(GLFWwindow* handle, int focused) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		window.m_Focused = focused == GLFW_TRUE;
		WindowFocusEvent event{window.m_Focused};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowIconifyCallback(GLFWwindow* handle, int iconified) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		window.m_Minimized = iconified == GLFW_TRUE;
		WindowMinimizeEvent event{window.m_Minimized};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowMaximizeCallback(GLFWwindow* handle, int maximized) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		window.m_Maximized = maximized == GLFW_TRUE;
		WindowMaximizeEvent event{window.m_Maximized};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::DropCallback(GLFWwindow* handle, int pathCount, const char* paths[]) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		WindowPathDropEvent event{static_cast<uint32_t>(pathCount), paths};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowContentScaleCallback(GLFWwindow* handle, float scaleX, float scaleY) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		WindowContentScaleEvent event{scaleX, scaleY};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowRefreshCallback(GLFWwindow* handle) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		WindowRefreshEvent event;
		window.m_EventCallback(event, &window);
	}

	// Key Callbacks

	auto WindowsWindow::KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};

		switch (action)
		{
			break;case GLFW_PRESS:
			{
				KeyPressEvent event{UnconvertKeycodeFromGLFW(key), UnconvertModifiersFromGLFW(mods)};
				window.m_EventCallback(event, &window);
			}
			break;case GLFW_REPEAT:
			{
				KeyRepeatEvent event{UnconvertKeycodeFromGLFW(key), UnconvertModifiersFromGLFW(mods)};
				window.m_EventCallback(event, &window);
			}
			break;case GLFW_RELEASE:
			{
				KeyReleaseEvent event{UnconvertKeycodeFromGLFW(key), UnconvertModifiersFromGLFW(mods)};
				window.m_EventCallback(event, &window);
			}
		}
	}

	auto WindowsWindow::CharCallback(GLFWwindow* handle, unsigned int codepoint) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		KeyCharTypeEvent event{static_cast<Codepoint>(codepoint)};
		window.m_EventCallback(event, &window);
	}

	// Mouse Callbacks

	auto WindowsWindow::MouseButtonCallback(GLFWwindow* handle, int button, int action, int mods) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};

		switch (action)
		{
			break;case GLFW_PRESS:
			{
				MouseButtonPressEvent event{UnconvertMouseButtonFromGLFW(button), UnconvertModifiersFromGLFW(mods)};
				window.m_EventCallback(event, &window);
			}
			break;case GLFW_RELEASE:
			{
				MouseButtonReleaseEvent event{UnconvertMouseButtonFromGLFW(button), UnconvertModifiersFromGLFW(mods)};
				window.m_EventCallback(event, &window);
			}
		}
	}

	auto WindowsWindow::CursorPosCallback(GLFWwindow* handle, double x, double y) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		MouseMoveEvent event{static_cast<float>(x), static_cast<float>(y)};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::ScrollCallback(GLFWwindow* handle, double offsetX, double offsetY) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		MouseScrollEvent event{static_cast<float>(offsetX), static_cast<float>(offsetY)};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::CursorEnterCallback(GLFWwindow* handle, int entered) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		MouseEnterEvent event{entered == GLFW_TRUE};
		window.m_EventCallback(event, &window);
	}
}
