#pragma once

#include "GBC/Event/Event.h"
#include <functional>

namespace gbc
{
	struct WindowInfo
	{
		uint32_t width{1280};
		uint32_t height{720};
		std::string title{"GBC"};

		// Flags
		bool vsync : 1 {true};
	};

	class Window;
	using EventCallback = std::function<auto(Event&, Window*) -> void>;

	class Window
	{
	public:
		static Scope<Window> CreateScope(const WindowInfo& info = {});
		virtual ~Window() = default;
	public:
		virtual auto SetEventCallback(const EventCallback& callback) -> EventCallback = 0;
		virtual auto SwapBuffers() -> void = 0;
		virtual auto ShouldClose() const -> bool = 0;
		virtual auto Close() -> void = 0;
	public:
		virtual auto SetTitle(std::string_view title) -> void = 0;
		virtual auto GetTitle() const -> std::string = 0;
	public:
		virtual auto SetVSync(bool enabled) -> void = 0;
		virtual auto IsVSync() const -> bool = 0;
		virtual auto ToggleVSync() -> void = 0;
	};
}
