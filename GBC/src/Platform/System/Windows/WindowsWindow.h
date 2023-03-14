#pragma once

#include "GBC/Core/Window.h"
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

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
		inline virtual auto GetWidth() const -> uint32_t { return m_Width; }
		inline virtual auto GetHeight() const -> uint32_t { return m_Height; }
	public:
		virtual auto SetTitle(std::string_view title) -> void override;
		inline virtual auto GetTitle() const -> std::string override { return m_Title; }
	public:
		virtual auto SetVSync(bool enabled) -> void override;
		inline virtual auto IsVSync() const -> bool override { return m_VSync; }
		inline virtual auto ToggleVSync() -> void override { SetVSync(!IsVSync()); }
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
		static auto DropCallback(GLFWwindow* handle, int pathCount, const char** paths) -> void;
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
		GLFWwindow* m_Handle{nullptr};

		EventCallback m_EventCallback;
		std::string m_Title;

		// State
		uint32_t m_Width{0};
		uint32_t m_Height{0};

		// Flags
		bool m_VSync : 1 {false};
		bool m_ShouldClose : 1 {false};
	};
}
