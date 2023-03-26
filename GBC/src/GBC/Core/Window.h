#pragma once

#include "GBC/Event/Event.h"
#include <glm/glm.hpp>
#include <functional>

namespace gbc
{
	struct WindowInfo
	{
		int32_t width{1280};
		int32_t height{720};
		std::string title{"GBC"};

		// Flags
		bool vsync : 1 {true};
	};

	class Window;
	using EventCallback = std::function<auto(Event&, Window*) -> void>;

	class Window
	{
	public:
		static auto CreateScope(const WindowInfo& info = {}) -> Scope<Window>;
		virtual ~Window() = default;
	public:
		virtual auto GetNativeWindow() -> void* = 0;
		virtual auto SetEventCallback(const EventCallback& callback) -> void = 0;
		virtual auto SwapBuffers() -> void = 0;
		virtual auto Close() -> void = 0;
		virtual auto ShouldClose() -> bool = 0;
	public:
		virtual auto GetWidth() const -> int32_t = 0;
		virtual auto GetHeight() const -> int32_t = 0;
		virtual auto GetSize() const -> glm::ivec2 = 0;
		virtual auto GetFramebufferWidth() const -> int32_t = 0;
		virtual auto GetFramebufferHeight() const -> int32_t = 0;
		virtual auto GetFramebufferSize() const -> glm::ivec2 = 0;
	public:
		virtual auto SetTitle(std::string_view title) -> void = 0;
		virtual auto GetTitle() const -> std::string = 0;
	public:
		virtual auto SetVSync(bool enabled) -> void = 0;
		virtual auto IsVSync() const -> bool = 0;
		virtual auto ToggleVSync() -> void = 0;
	};
}
