#pragma once

#include "GBC/Core/Window.h"
#include "GBC/Rendering/Context.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

namespace gbc
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowInfo& info);
		virtual ~WindowsWindow();
	public:
		inline virtual auto GetNativeWindow() -> void* override { return m_Handle; }
		virtual auto SetEventCallback(const EventCallback& callback) -> void override;
		virtual auto SwapBuffers() -> void override;
		virtual auto Close() -> void override;
		virtual auto ShouldClose() -> bool override;
	public:
		inline virtual auto GetWidth() const -> uint32_t { return m_Current.size.x; }
		inline virtual auto GetHeight() const -> uint32_t { return m_Current.size.y; }
		inline virtual auto GetFramebufferWidth() const -> uint32_t { return m_FramebufferWidth; }
		inline virtual auto GetFramebufferHeight() const -> uint32_t { return m_FramebufferHeight; }
	public:
		inline virtual auto SetTitle(std::string_view title) -> void override { if (m_Title != title) Impl_SetTitle(title); }
		inline virtual auto GetTitle() const -> std::string_view override { return m_Title; }
	public:
		inline virtual auto SetWindowMode(WindowMode windowMode) -> void override { if (m_WindowMode != windowMode) Impl_SetWindowMode(windowMode); }
		inline virtual auto GetWindowMode() const -> WindowMode override { return m_WindowMode; }
	public:
		inline virtual auto SetVSync(bool enabled) -> void override { if (m_VSync != !!enabled) Impl_SetVSync(!!enabled); }
		inline virtual auto IsVSync() const -> bool override { return m_VSync; }
		inline virtual auto ToggleVSync() -> void override { SetVSync(!IsVSync()); }
	public:
		inline virtual auto SetResizable(bool enabled) -> void override { if (m_Resizable != !!enabled) Impl_SetResizable(!!enabled); }
		inline virtual auto IsResizable() const -> bool override { return m_Resizable; }
		inline virtual auto ToggleResizable() -> void override { SetResizable(!IsResizable()); }
	public:
		inline virtual auto SetMouseCaptured(bool enabled) -> void override { if (m_MouseCaptured != !!enabled) Impl_SetMouseCaptured(!!enabled); }
		inline virtual auto IsMouseCaptured() const -> bool override { return m_MouseCaptured; }
		inline virtual auto ToggleMouseCaptured() -> void override { SetMouseCaptured(!IsMouseCaptured()); }
	private:
		auto Impl_SetTitle(std::string_view title) -> void;
		auto Impl_SetVSync(bool enabled) -> void;
		auto Impl_SetResizable(bool enabled) -> void;
		auto Impl_SetWindowMode(WindowMode windowMode) -> void;
		auto Impl_SetMouseCaptured(bool enabled) -> void;
	private:
		auto GetWindowMonitor(GLFWmonitor*& outMonitor, glm::ivec2& outMonitorPos, glm::uvec2& outMonitorSize) -> void;
	private:
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
	private:
		GLFWwindow* m_Handle{};

		Scope<Context> m_Context;
		EventCallback m_EventCallback;
		std::string m_Title;

		// State
		uint32_t m_FramebufferWidth{};
		uint32_t m_FramebufferHeight{};

		struct
		{
			glm::ivec2 position{0};
			glm::uvec2 size{0};
		} m_Current, m_Backup;

		// Flags
		bool m_VSync            : 1 {};
		bool m_Resizable        : 1 {};
		bool m_MouseCaptured    : 1 {};
		bool m_Focused          : 1 {};
		bool m_Maximized        : 1 {};
		bool m_Minimized        : 1 {};
		bool m_ShouldClose      : 1 {};
		WindowMode m_WindowMode : WindowMode::BitCount {};
	};
}
