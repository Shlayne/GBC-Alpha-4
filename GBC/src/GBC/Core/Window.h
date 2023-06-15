#pragma once

#include "GBC/Event/Event.h"
#include <glm/glm.hpp>

namespace gbc
{
	GBC_DEFINE_BOUNDED_ENUM(
		WindowMode, uint8_t,

		Windowed,
		Fullscreen,
		BorderlessWindowed
	);

	struct WindowInfo
	{
		uint32_t width{1280};
		uint32_t height{720};
		std::string title{"GBC"};

		// Flags
		bool vsync            : 1 {true};
		bool resizable        : 1 {true};
		bool mouseCaptured    : 1 {false};
		bool focused          : 1 {true};
		bool maximized        : 1 {false};
		WindowMode windowMode : WindowMode::BitCount {WindowMode::Windowed};
	};

	class Window
	{
	public:
		static inline auto CreateScope(const WindowInfo& info) -> Scope<Window> { return gbc::CreateScope<Window>(info); }
		Window(const WindowInfo& info);
		~Window();
	public:
		auto GetNativeWindow() -> void*;
		auto SetEventCallback(const EventCallback& callback) -> void;
		auto SwapBuffers() -> void;
		auto Close() -> void;
		auto ShouldClose() -> bool;
	public:
		auto GetWidth() const -> uint32_t;
		auto GetHeight() const -> uint32_t;
		auto GetFramebufferWidth() const -> uint32_t;
		auto GetFramebufferHeight() const -> uint32_t;
	public:
		auto SetTitle(std::string_view title) -> void;
		auto GetTitle() const -> std::string_view;
	public:
		auto SetWindowMode(WindowMode windowMode) -> void;
		auto GetWindowMode() const -> WindowMode;
	public:
		auto SetVSync(bool enabled) -> void;
		auto IsVSync() const -> bool;
		auto ToggleVSync() -> void;
	public:
		auto SetResizable(bool enabled) -> void;
		auto IsResizable() const -> bool;
		auto ToggleResizable() -> void;
	public:
		auto SetMouseCaptured(bool enabled) -> void;
		auto IsMouseCaptured() const -> bool;
		auto ToggleMouseCaptured() -> void;
	private:
		struct Data;
		Data* m_Data{}; // Implementation without vtable overhead.
	};
}
