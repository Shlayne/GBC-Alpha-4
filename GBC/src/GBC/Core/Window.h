#pragma once

#include "GBC/Event/Event.h"
#include <glm/glm.hpp>
#include <functional>

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

	class Window;
	using EventCallback = std::function<auto(Event&, Window*) -> void>;

	class Window
	{
	public:
		static auto CreateScope(const WindowInfo& info) -> Scope<Window>;
		virtual ~Window() = default;
	public:
		virtual auto GetNativeWindow() -> void* = 0;
		virtual auto SetEventCallback(const EventCallback& callback) -> void = 0;
		virtual auto SwapBuffers() -> void = 0;
		virtual auto Close() -> void = 0;
		virtual auto ShouldClose() -> bool = 0;
	public:
		virtual auto GetWidth() const -> uint32_t = 0;
		virtual auto GetHeight() const -> uint32_t = 0;
		virtual auto GetFramebufferWidth() const -> uint32_t = 0;
		virtual auto GetFramebufferHeight() const -> uint32_t = 0;
	public:
		virtual auto SetTitle(std::string_view title) -> void = 0;
		virtual auto GetTitle() const -> std::string_view = 0;
	public:
		virtual auto SetWindowMode(WindowMode windowMode) -> void = 0;
		virtual auto GetWindowMode() const -> WindowMode = 0;
	public:
		virtual auto SetVSync(bool enabled) -> void = 0;
		virtual auto IsVSync() const -> bool = 0;
		virtual auto ToggleVSync() -> void = 0;
	public:
		virtual auto SetResizable(bool enabled) -> void = 0;
		virtual auto IsResizable() const -> bool = 0;
		virtual auto ToggleResizable() -> void = 0;
	public:
		virtual auto SetMouseCaptured(bool enabled) -> void = 0;
		virtual auto IsMouseCaptured() const -> bool = 0;
		virtual auto ToggleMouseCaptured() -> void = 0;
	};
}
