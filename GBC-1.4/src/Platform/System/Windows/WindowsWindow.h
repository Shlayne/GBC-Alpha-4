#pragma once

#include "GBC/Core/Window.h"
#include <glfw/glfw3.h>

namespace gbc
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowInfo& info);
		virtual ~WindowsWindow();
	public:
		virtual auto SetEventCallback(const EventCallback& callback) -> EventCallback override;
		virtual auto SwapBuffers() -> void override;
		virtual auto ShouldClose() const -> bool override;
		virtual auto Close() -> void override;
	public:
		virtual auto SetTitle(std::string_view title) -> void override;
		inline virtual auto GetTitle() const -> std::string override { return m_Data.title; }
	public:
		virtual auto SetVSync(bool enabled) -> void override;
		inline virtual auto IsVSync() const -> bool override { return m_Data.vsync; }
		inline virtual auto ToggleVSync() -> void override { SetVSync(!IsVSync()); }
	private:
		GLFWwindow* m_Window{nullptr};

		struct WindowData
		{
			EventCallback eventCallback;
			std::string title;

			// Flags
			bool vsync : 1 {false};
			bool shouldClose : 1 {false};
		} m_Data;
	};
}
