#include "gbcpch.h"
#include "WindowsWindow.h"

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
		}
		{
			// TODO: profile scope
			m_Window = glfwCreateWindow(static_cast<int>(info.width), static_cast<int>(info.height), info.title.data(), nullptr, nullptr);
			GBC_CORE_ASSERT(!!m_Window, "Failed to create GLFW window.");
			++s_WindowCount;
		}
		{
			// TODO: profile scope
			glfwMakeContextCurrent(m_Window);
		}
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(info.vsync);
		SetTitle(info.title);
	}

	WindowsWindow::~WindowsWindow()
	{
		GBC_CORE_ASSERT(s_WindowCount > 0, "Tried to redestroy a window.");

		glfwDestroyWindow(m_Window);
		if (!--s_WindowCount)
			glfwTerminate();
	}

	auto WindowsWindow::SetEventCallback(const EventCallback& callback) -> EventCallback
	{
		EventCallback oldCallback = m_Data.eventCallback;
		m_Data.eventCallback = callback;
		return oldCallback;
	}

	auto WindowsWindow::SwapBuffers() -> void
	{
		glfwPollEvents(); // TODO: move poll events to its own file so it's only called once per game loop iteration.
		glfwSwapBuffers(m_Window);
	}

	auto WindowsWindow::ShouldClose() const -> bool
	{
		return m_Data.shouldClose || glfwWindowShouldClose(m_Window);
	}

	auto WindowsWindow::Close() -> void
	{
		m_Data.shouldClose = true;
	}

	auto WindowsWindow::SetTitle(std::string_view title) -> void
	{
		glfwSetWindowTitle(m_Window, title.data());
	}

	auto WindowsWindow::SetVSync(bool enabled) -> void
	{
		if (m_Data.vsync != enabled)
			glfwSwapInterval(m_Data.vsync = enabled);
	}
}
