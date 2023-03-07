#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Core/Window.h"
#include "GBC/Event/Events.h"
#include <vector>

namespace gbc
{
	class ApplicationCommandLineArgs
	{
	public:
		ApplicationCommandLineArgs() noexcept = default;
		ApplicationCommandLineArgs(int argc, char** argv);
	public:
		auto operator[](size_t index) const noexcept -> const char*;
	private:
		int m_Count{0};
		char** m_Args{nullptr};
	};

	struct ApplicationInfo
	{
		ApplicationCommandLineArgs args;
	};

	class Application
	{
	public:
		Application(const ApplicationInfo& info);
		virtual ~Application();
	public:
		static auto Get() -> Application&;
		auto GetWindow(size_t index = 0) -> Window&;
		auto OpenWindow(const WindowInfo& info) -> Window&;
	public:
		inline auto GetCommandLineArgs() -> ApplicationCommandLineArgs { return m_CommandLineArgs; }
	private:
		auto OnEvent(Event& event, Window* window) -> void;
		auto OnWindowCloseEvent(WindowCloseEvent& event, Window* window) -> void;
	private:
		ApplicationCommandLineArgs m_CommandLineArgs;
		std::vector<Scope<Window>> m_Windows;

		// Flags
		bool m_Running : 1 {false};
	private:
		friend auto Main(int argc, char** argv) -> int;
		auto Run() -> void;
	};
}
