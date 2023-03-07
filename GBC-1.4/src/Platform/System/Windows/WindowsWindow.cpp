#include "gbcpch.h"
#include "WindowsWindow.h"
#include "GBC/Event/Events.h"

namespace gbc
{
	Scope<Window> Window::CreateScope(const WindowInfo& info)
	{
		return ::gbc::CreateScope<WindowsWindow>(info);
	}

	uint32_t s_WindowCount{0};

	WindowsWindow::WindowsWindow(const WindowInfo& info)
	{
		// TODO: profile scope

		if (!s_WindowCount)
		{
			// TODO: profile scope
			GBC_CORE_VERIFY(glfwInit(), "Failed to initialize GLFW.");

			SetCallbacks();
		}
		{
			// TODO: profile scope
			m_Handle = glfwCreateWindow(static_cast<int>(info.width), static_cast<int>(info.height), info.title.data(), nullptr, nullptr);
			GBC_CORE_ASSERT(m_Handle, "Failed to create GLFW window.");
			++s_WindowCount;
		}
		{
			// TODO: profile scope
			glfwMakeContextCurrent(m_Handle);
		}
		glfwSetWindowUserPointer(m_Handle, this);
		SetVSync(info.vsync);
		m_Title = info.title;

		SetWindowCallbacks(m_Handle);
	}

	WindowsWindow::~WindowsWindow()
	{
		GBC_CORE_ASSERT(s_WindowCount > 0, "Tried to redestroy a window.");

		{
			// TODO: profile scope
			glfwDestroyWindow(m_Handle);
		}
		if (!--s_WindowCount)
		{
			// TODO: profile scope
			glfwTerminate();
		}
	}

	auto WindowsWindow::SetEventCallback(const EventCallback& callback) -> EventCallback
	{
		EventCallback oldCallback = m_EventCallback;
		m_EventCallback = callback;
		return oldCallback;
	}

	auto WindowsWindow::SwapBuffers() -> void
	{
		glfwSwapBuffers(m_Handle);
	}

	auto WindowsWindow::PollEvents() -> void
	{
		glfwPollEvents(); // TODO: move poll events to its own file.
	}

	auto WindowsWindow::Close() -> void
	{
		// Send a fake close event that only the Application pays attention to.
		WindowCloseEvent event{true};
		m_EventCallback(event, this);
	}

	auto WindowsWindow::SetTitle(std::string_view title) -> void
	{
		m_Title = title;
		glfwSetWindowTitle(m_Handle, title.data());
	}

	auto WindowsWindow::SetVSync(bool enabled) -> void
	{
		if (m_VSync != enabled)
			glfwSwapInterval(!!(m_VSync = enabled));
	}

	auto WindowsWindow::SetCallbacks() -> void
	{
		// Miscellaneous Callbacks
#if GBC_ENABLE_LOGGING
		glfwSetErrorCallback(&WindowsWindow::ErrorCallback);
#endif
		// TODO: monitor and joystick callbacks would go here.
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
		WindowResizeEvent event{static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::FramebufferSizeCallback(GLFWwindow* handle, int width, int height) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		WindowFramebufferResizeEvent event{static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowPosCallback(GLFWwindow* handle, int x, int y) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		WindowMoveEvent event{static_cast<int32_t>(x), static_cast<int32_t>(y)};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowFocusCallback(GLFWwindow* handle, int focused) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		WindowFocusEvent event{focused == GLFW_TRUE};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowIconifyCallback(GLFWwindow* handle, int iconified) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		WindowMinimizeEvent event{iconified == GLFW_TRUE};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::WindowMaximizeCallback(GLFWwindow* handle, int maximized) -> void
	{
		WindowsWindow& window{*static_cast<WindowsWindow*>(glfwGetWindowUserPointer(handle))};
		WindowMaximizeEvent event{maximized == GLFW_TRUE};
		window.m_EventCallback(event, &window);
	}

	auto WindowsWindow::DropCallback(GLFWwindow* handle, int pathCount, const char** paths) -> void
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
				KeyPressEvent event{static_cast<Keycode>(key), static_cast<Modifiers>(mods)};
				window.m_EventCallback(event, &window);
			}
			break;case GLFW_REPEAT:
			{
				KeyRepeatEvent event{static_cast<Keycode>(key), static_cast<Modifiers>(mods)};
				window.m_EventCallback(event, &window);
			}
			break;case GLFW_RELEASE:
			{
				KeyReleaseEvent event{static_cast<Keycode>(key), static_cast<Modifiers>(mods)};
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
				MouseButtonPressEvent event{static_cast<MouseButton>(button), static_cast<Modifiers>(mods)};
				window.m_EventCallback(event, &window);
			}
			break;case GLFW_RELEASE:
			{
				MouseButtonReleaseEvent event{static_cast<MouseButton>(button), static_cast<Modifiers>(mods)};
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

	// Miscellaneous Callbacks

#if GBC_ENABLE_LOGGING
	auto WindowsWindow::ErrorCallback(int errorCode, const char* description) -> void
	{
		GBC_CORE_ERROR("GLFW Error ({}): {}", errorCode, description);
	}
#endif
}
