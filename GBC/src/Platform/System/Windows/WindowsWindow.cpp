#include "gbcpch.h"
#include "GBC/Core/Window.h"
#include "GBC/Event/Events.h"
#include "GBC/Rendering/Context.h"
#include "WindowsConversions.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>
#if GBC_CONFIG_DEBUG
	#include "GBC/Rendering/RendererAPI.h"
#endif

namespace gbc
{
	struct Window::Data
	{
		static auto SetWindowCallbacks(GLFWwindow* handle) -> void;

		// Window Callbacks
		static auto WindowCloseCallback(GLFWwindow* handle) -> void;
		static auto WindowSizeCallback(GLFWwindow* handle, int width, int height) -> void;
		static auto FramebufferSizeCallback(GLFWwindow* handle, int width, int height) -> void;
		static auto WindowPosCallback(GLFWwindow* handle, int x, int y) -> void;
		static auto WindowFocusCallback(GLFWwindow* handle, int focused) -> void;
		static auto WindowIconifyCallback(GLFWwindow* handle, int iconified) -> void;
		static auto WindowMaximizeCallback(GLFWwindow* handle, int maximized) -> void;
		static auto DropCallback(GLFWwindow* handle, int pathCount, const char* paths[]) -> void;
		static auto WindowContentScaleCallback(GLFWwindow* handle, float scaleX, float scaleY) -> void;
		static auto WindowRefreshCallback(GLFWwindow* handle) -> void;

		// Key Callbacks
		static auto KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods) -> void;
		static auto CharCallback(GLFWwindow* handle, unsigned int codepoint) -> void;

		// Mouse Callbacks
		static auto MouseButtonCallback(GLFWwindow* handle, int button, int action, int mods) -> void;
		static auto CursorPosCallback(GLFWwindow* handle, double x, double y) -> void;
		static auto ScrollCallback(GLFWwindow* handle, double offsetX, double offsetY) -> void;
		static auto CursorEnterCallback(GLFWwindow* handle, int entered) -> void;

		auto SetTitle(std::string_view title) -> void;
		auto SetVSync(bool enabled) -> void;
		auto SetResizable(bool enabled) -> void;
		auto SetWindowMode(WindowMode windowMode) -> void;
		auto SetMouseCaptured(bool enabled) -> void;

		auto GetWindowMonitor(GLFWmonitor** outMonitor, glm::ivec2& outMonitorPos, glm::uvec2& outMonitorSize, int32_t* outRefreshRate) -> void;

		GLFWwindow* handle{};

		Scope<Context> context;
		EventCallback eventCallback;
		std::string title;

		// State
		uint32_t framebufferWidth{};
		uint32_t framebufferHeight{};

		struct
		{
			glm::ivec2 position{0};
			glm::uvec2 size{0};
		} current, backup;

		// Flags
		bool vsync            : 1 {};
		bool resizable        : 1 {};
		bool mouseCaptured    : 1 {};
		bool focused          : 1 {};
		bool maximized        : 1 {};
		bool minimized        : 1 {};
		bool shouldClose      : 1 {};
		WindowMode windowMode : WindowMode::BitCount {};
	};

	Window::Window(const WindowInfo& info)
		: m_Data{new Data{}}
	{
		// TODO: profile function
		
		auto& data{*m_Data};

		data.title = info.title;
		data.vsync = !!info.vsync;
		data.resizable = !!info.resizable;
		data.mouseCaptured = !!info.mouseCaptured;
		data.focused = !!info.focused;
		data.maximized = !!info.maximized;
		data.windowMode = info.windowMode;

		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(WindowMode, data.windowMode);

		// Set appropriate window hints.
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, data.resizable);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, data.focused);
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

		switch (data.windowMode)
		{
		case WindowMode::Windowed:
			data.current.size.x = info.width;
			data.current.size.y = info.height;
			break;
		case WindowMode::Fullscreen:
			fullscreenMonitor = defaultMonitor;
			// Using [[fallthrough]] makes this not compile, but intellisense warns if it's not used.
		case WindowMode::BorderlessWindowed:
			data.backup.size.x = info.width;
			data.backup.size.y = info.height;
			vidmode = glfwGetVideoMode(defaultMonitor);
			data.current.size.x = vidmode->width;
			data.current.size.y = vidmode->height;
			break;
		}

		// Actually create the window.
		{
			// TODO: profile scope
			data.handle = glfwCreateWindow(data.current.size.x, data.current.size.y, data.title.c_str(), fullscreenMonitor, nullptr);
			GBC_CORE_ASSERT(data.handle, "Failed to create GLFW window.");
		}

		int32_t left, top, right, bottom;
		glfwGetMonitorWorkarea(defaultMonitor, &left, &top, &right, &bottom);
		glm::ivec2 monitorWorkArea{right - left, bottom - top};
		glfwGetWindowFrameSize(data.handle, &left, &top, &right, &bottom);
		// Windows 10 always returns left = top = bottom = 8 for bordered windows (it should be 1)
		glm::ivec2 windowFrameSize{right + left, bottom + top - 7};
		glm::ivec2 windowPosition{glm::ivec2{left, top} + (monitorWorkArea - (glm::ivec2{data.current.size} + windowFrameSize)) / 2};

		if (data.windowMode == WindowMode::Windowed)
			data.current.position = windowPosition;
		else
			data.backup.position = windowPosition;

		glfwSetWindowPos(data.handle, data.current.position.x, data.current.position.y);
		glfwSetInputMode(data.handle, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
		glfwSetWindowUserPointer(data.handle, this);

		data.context = Context::CreateScope({data.handle});

		data.SetVSync(data.vsync);
		data.SetMouseCaptured(data.mouseCaptured);

		if (data.maximized)
		{
			glfwMaximizeWindow(data.handle);
			glfwGetWindowSize(data.handle, reinterpret_cast<int32_t*>(&data.current.size.x), reinterpret_cast<int32_t*>(&data.current.size.y));
			glfwGetWindowPos(data.handle, &data.current.position.x, &data.current.position.y);
		}

		glfwShowWindow(data.handle);
		data.SetWindowCallbacks(data.handle);
	}

	Window::~Window()
	{
		// TODO: profile function
		auto& data{*m_Data};
		glfwDestroyWindow(data.handle);
	}

	auto Window::GetNativeWindow() -> void*
	{
		auto& data{*m_Data};
		return data.handle;
	}

	auto Window::SetEventCallback(const EventCallback& callback) -> void
	{
		auto& data{*m_Data};
		data.eventCallback = callback;
	}

	auto Window::SwapBuffers() -> void
	{
		auto& data{*m_Data};
		data.context->SwapBuffers();
	}

	auto Window::Close() -> void
	{
		auto& data{*m_Data};
		data.shouldClose = true;
	}

	auto Window::ShouldClose() -> bool
	{
		auto& data{*m_Data};
		return data.shouldClose || glfwWindowShouldClose(data.handle);
	}

	auto Window::GetWidth() const -> uint32_t
	{
		auto& data{*m_Data};
		return data.current.size.x;
	}

	auto Window::GetHeight() const -> uint32_t
	{
		auto& data{*m_Data};
		return data.current.size.y;
	}

	auto Window::GetFramebufferWidth() const -> uint32_t
	{
		auto& data{*m_Data};
		return data.framebufferWidth;
	}

	auto Window::GetFramebufferHeight() const -> uint32_t
	{
		auto& data{*m_Data};
		return data.framebufferHeight;
	}
	
	auto Window::SetTitle(std::string_view title) -> void
	{
		auto& data{*m_Data};
		if (data.title != title)
			data.SetTitle(title);
	}

	auto Window::SetWindowMode(WindowMode windowMode) -> void
	{
		auto& data{*m_Data};
		if (data.windowMode != windowMode)
			data.SetWindowMode(windowMode);
	}

	auto Window::GetWindowMode() const -> WindowMode
	{
		auto& data{*m_Data};
		return data.windowMode;
	}

	auto Window::SetVSync(bool enabled) -> void
	{
		auto& data{*m_Data};
		if (data.vsync != !!enabled)
			data.SetVSync(!!enabled);
	}

	auto Window::IsVSync() const -> bool
	{
		auto& data{*m_Data};
		return data.vsync;
	}

	auto Window::ToggleVSync() -> void
	{
		SetVSync(!IsVSync());
	}

	auto Window::SetResizable(bool enabled) -> void
	{
		auto& data{*m_Data};
		if (data.resizable != !!enabled)
			data.SetResizable(!!enabled);
	}

	auto Window::IsResizable() const -> bool
	{
		auto& data{*m_Data};
		return data.resizable;
	}

	auto Window::ToggleResizable() -> void
	{
		SetResizable(!IsResizable());
	}

	auto Window::SetMouseCaptured(bool enabled) -> void
	{
		auto& data{*m_Data};
		if (data.mouseCaptured != !!enabled)
			data.SetMouseCaptured(!!enabled);
	}

	auto Window::IsMouseCaptured() const -> bool
	{
		auto& data{*m_Data};
		return data.mouseCaptured;
	}

	auto Window::ToggleMouseCaptured() -> void
	{
		SetMouseCaptured(!IsMouseCaptured());
	}

	auto Window::GetTitle() const -> std::string_view
	{
		auto& data{*m_Data};
		return data.title;
	}

	auto Window::Data::SetTitle(std::string_view title) -> void
	{
		auto& data{*this};
		glfwSetWindowTitle(data.handle, title.data());
		data.title = title;
	}

	auto Window::Data::SetVSync(bool enabled) -> void
	{
		auto& data{*this};
		glfwSwapInterval(enabled);
		data.vsync = enabled;
	}

	auto Window::Data::SetResizable(bool enabled) -> void
	{
		auto& data{*this};
		glfwSetWindowAttrib(data.handle, GLFW_RESIZABLE, enabled);
		data.resizable = enabled;
	}

	auto Window::Data::SetWindowMode(WindowMode windowMode) -> void
	{
		GBC_CORE_ASSERT_BOUNDED_ENUM_IS_VALID(WindowMode, windowMode);

		auto& data{*this};

		bool decorated{};
		glm::ivec2 windowPos{0};
		glm::uvec2 windowSize{0};
		int32_t refreshRate{GLFW_DONT_CARE};
		GLFWmonitor* monitor{};
		GLFWmonitor** monitorPointer{};

		switch (windowMode)
		{
		case WindowMode::Windowed:
			windowPos = data.backup.position;
			windowSize = data.backup.size;
			decorated = true;
			break;
		case WindowMode::Fullscreen:
			monitorPointer = &monitor;
			// Fallthrough
		case WindowMode::BorderlessWindowed:
			if (data.windowMode == WindowMode::Windowed)
				data.backup = data.current;
			GetWindowMonitor(monitorPointer, windowPos, windowSize, data.vsync ? &refreshRate : nullptr);
			break;
		}

		glfwSetWindowMonitor(data.handle, monitor, windowPos.x, windowPos.y, windowSize.x, windowSize.y, refreshRate);
		glfwSetWindowAttrib(data.handle, GLFW_DECORATED, decorated);
		data.SetVSync(data.vsync);

		data.windowMode = windowMode;
	}

	auto Window::Data::SetMouseCaptured(bool enabled) -> void
	{
		auto& data{*this};
		glfwSetInputMode(data.handle, GLFW_CURSOR, enabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		data.mouseCaptured = enabled;
	}

	auto Window::Data::GetWindowMonitor(GLFWmonitor** outMonitor, glm::ivec2& outMonitorPos, glm::uvec2& outMonitorSize, int32_t* outRefreshRate) -> void
	{
		auto& data{*this};

		// From: https://stackoverflow.com/questions/21421074/how-to-create-a-full-screen-window-on-the-current-monitor-with-glfw
		// Get the monitor that most of the window is on. There is a Windows function for this, but it's not exposed via glfw :/
		int32_t largestOverlap{INT_MIN};

		int32_t monitorCount;
		GLFWmonitor** monitors{glfwGetMonitors(&monitorCount)};

		for (int32_t i{}; i < monitorCount; ++i)
		{
			const GLFWvidmode* videoMode{glfwGetVideoMode(monitors[i])};

			int32_t monitorX, monitorY;
			glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);

			int32_t overlapX{std::max(0, std::min(data.current.position.x + static_cast<int32_t>(data.current.size.x), monitorX + videoMode->width) - std::max(data.current.position.x, monitorX))};
			int32_t overlapY{std::max(0, std::min(data.current.position.y + static_cast<int32_t>(data.current.size.y), monitorY + videoMode->height) - std::max(data.current.position.y, monitorY))};
			int32_t overlap{overlapX * overlapY};

			if (overlap > largestOverlap)
			{
				largestOverlap = overlap;
				if (outMonitor)
					*outMonitor = monitors[i];
				outMonitorPos = {monitorX, monitorY};
				outMonitorSize = {static_cast<uint32_t>(videoMode->width), static_cast<uint32_t>(videoMode->height)};
				if (outRefreshRate)
					*outRefreshRate = videoMode->refreshRate;
			}
		}
	}

	auto Window::Data::SetWindowCallbacks(GLFWwindow* handle) -> void
	{
		// Window Events
		glfwSetWindowCloseCallback(handle, &Window::Data::WindowCloseCallback);
		glfwSetWindowSizeCallback(handle, &Window::Data::WindowSizeCallback);
		glfwSetFramebufferSizeCallback(handle, &Window::Data::FramebufferSizeCallback);
		glfwSetWindowPosCallback(handle, &Window::Data::WindowPosCallback);
		glfwSetWindowFocusCallback(handle, &Window::Data::WindowFocusCallback);
		glfwSetWindowIconifyCallback(handle, &Window::Data::WindowIconifyCallback);
		glfwSetWindowMaximizeCallback(handle, &Window::Data::WindowMaximizeCallback);
		glfwSetDropCallback(handle, &Window::Data::DropCallback);
		glfwSetWindowContentScaleCallback(handle, &Window::Data::WindowContentScaleCallback);
		glfwSetWindowRefreshCallback(handle, &Window::Data::WindowRefreshCallback);

		// Key Events
		glfwSetKeyCallback(handle, &Window::Data::KeyCallback);
		glfwSetCharCallback(handle, &Window::Data::CharCallback);

		// Mouse Events
		glfwSetMouseButtonCallback(handle, &Window::Data::MouseButtonCallback);
		glfwSetCursorPosCallback(handle, &Window::Data::CursorPosCallback);
		glfwSetScrollCallback(handle, &Window::Data::ScrollCallback);
		glfwSetCursorEnterCallback(handle, &Window::Data::CursorEnterCallback);
	}

	// Window Callbacks

	auto Window::Data::WindowCloseCallback(GLFWwindow* handle) -> void
	{
		// TODO: for now, assuming the user pointer is nonnull is fine.
		// However, if ImGui events are made to chain these callbacks,
		// then that will have to change, in addition to moving the
		// event callback to the Input class and having it be accessible
		// by any Window subclass, including Window.
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		WindowCloseEvent event;
		data.eventCallback(event, &window);
	}

	auto Window::Data::WindowSizeCallback(GLFWwindow* handle, int width, int height) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		data.current.size = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
		WindowResizeEvent event{data.current.size.x, data.current.size.y};
		data.eventCallback(event, &window);
	}

	auto Window::Data::FramebufferSizeCallback(GLFWwindow* handle, int width, int height) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		data.framebufferWidth = static_cast<uint32_t>(width);
		data.framebufferHeight = static_cast<uint32_t>(height);
		WindowFramebufferResizeEvent event{data.framebufferWidth, data.framebufferHeight};
		data.eventCallback(event, &window);
	}

	auto Window::Data::WindowPosCallback(GLFWwindow* handle, int x, int y) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		data.current.position = {static_cast<uint32_t>(x), static_cast<uint32_t>(y)};
		WindowMoveEvent event{data.current.position.x, data.current.position.y};
		data.eventCallback(event, &window);
	}

	auto Window::Data::WindowFocusCallback(GLFWwindow* handle, int focused) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		data.focused = focused == GLFW_TRUE;
		WindowFocusEvent event{data.focused};
		data.eventCallback(event, &window);
	}

	auto Window::Data::WindowIconifyCallback(GLFWwindow* handle, int iconified) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		data.minimized = iconified == GLFW_TRUE;
		WindowMinimizeEvent event{data.minimized};
		data.eventCallback(event, &window);
	}

	auto Window::Data::WindowMaximizeCallback(GLFWwindow* handle, int maximized) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		data.maximized = maximized == GLFW_TRUE;
		WindowMaximizeEvent event{data.maximized};
		data.eventCallback(event, &window);
	}

	auto Window::Data::DropCallback(GLFWwindow* handle, int pathCount, const char* paths[]) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		WindowPathDropEvent event{static_cast<uint32_t>(pathCount), paths};
		data.eventCallback(event, &window);
	}

	auto Window::Data::WindowContentScaleCallback(GLFWwindow* handle, float scaleX, float scaleY) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		WindowContentScaleEvent event{scaleX, scaleY};
		data.eventCallback(event, &window);
	}

	auto Window::Data::WindowRefreshCallback(GLFWwindow* handle) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		WindowRefreshEvent event;
		data.eventCallback(event, &window);
	}

	// Key Callbacks

	auto Window::Data::KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};

		switch (action)
		{
			break;case GLFW_PRESS:
			{
				KeyPressEvent event{UnconvertKeycodeFromGLFW(key), UnconvertModifiersFromGLFW(mods)};
				data.eventCallback(event, &window);
			}
			break;case GLFW_REPEAT:
			{
				KeyRepeatEvent event{UnconvertKeycodeFromGLFW(key), UnconvertModifiersFromGLFW(mods)};
				data.eventCallback(event, &window);
			}
			break;case GLFW_RELEASE:
			{
				KeyReleaseEvent event{UnconvertKeycodeFromGLFW(key), UnconvertModifiersFromGLFW(mods)};
				data.eventCallback(event, &window);
			}
		}
	}

	auto Window::Data::CharCallback(GLFWwindow* handle, unsigned int codepoint) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		KeyCharTypeEvent event{static_cast<Codepoint>(codepoint)};
		data.eventCallback(event, &window);
	}

	// Mouse Callbacks

	auto Window::Data::MouseButtonCallback(GLFWwindow* handle, int button, int action, int mods) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};

		switch (action)
		{
			break;case GLFW_PRESS:
			{
				MouseButtonPressEvent event{UnconvertMouseButtonFromGLFW(button), UnconvertModifiersFromGLFW(mods)};
				data.eventCallback(event, &window);
			}
			break;case GLFW_RELEASE:
			{
				MouseButtonReleaseEvent event{UnconvertMouseButtonFromGLFW(button), UnconvertModifiersFromGLFW(mods)};
				data.eventCallback(event, &window);
			}
		}
	}

	auto Window::Data::CursorPosCallback(GLFWwindow* handle, double x, double y) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		MouseMoveEvent event{static_cast<float>(x), static_cast<float>(y)};
		data.eventCallback(event, &window);
	}

	auto Window::Data::ScrollCallback(GLFWwindow* handle, double offsetX, double offsetY) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		MouseScrollEvent event{static_cast<float>(offsetX), static_cast<float>(offsetY)};
		data.eventCallback(event, &window);
	}

	auto Window::Data::CursorEnterCallback(GLFWwindow* handle, int entered) -> void
	{
		Window& window{*static_cast<Window*>(glfwGetWindowUserPointer(handle))};
		auto& data{*window.m_Data};
		MouseEnterEvent event{entered == GLFW_TRUE};
		data.eventCallback(event, &window);
	}
}
