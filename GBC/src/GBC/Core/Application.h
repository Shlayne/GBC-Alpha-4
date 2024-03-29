#pragma once

#include "GBC/Core/Core.h"
#include "GBC/Core/LayerStack.h"
#include "GBC/Core/System.h"
#include "GBC/Core/Window.h"
#include "GBC/Event/Events.h"
#include "GBC/Event/EventThread.h"
#include "GBC/ImGui/ImGuiOverlay.h"
#include <vector>

namespace gbc
{
	class ApplicationCommandLineArgs
	{
	public:
		constexpr ApplicationCommandLineArgs() noexcept = default;
		constexpr ApplicationCommandLineArgs(int argc, char* argv[]) : m_Count{argc} , m_Args{argv} {}
	public:
		constexpr auto operator[](size_t index) const noexcept -> const char* { return m_Args[index]; }
	private:
		int m_Count{};
		char** m_Args{};
	};

	struct ApplicationInfo
	{
		ApplicationCommandLineArgs commandLineArgs;
		WindowInfo primaryWindowInfo;
	};

	class Application
	{
	public:
		Application(const ApplicationInfo& info);
		virtual ~Application();
	public:
		inline auto Close() noexcept { m_Running = false; }
	public:
		static auto Get() -> Application&;
		auto GetWindow(size_t index = 0) -> Window&;
		auto OpenWindow(const WindowInfo& info) -> Window&;
		inline auto GetCommandLineArgs() const noexcept -> ApplicationCommandLineArgs { return m_CommandLineArgs; }
	public:
		auto PushLayer(Layer* layer) -> void;
		auto PopLayer() -> Layer*;
		auto PushOverlay(Layer* overlay) -> void;
		auto PopOverlay() -> Layer*;
	private:
		auto OnEvent(Event& event, Window* window) -> void;
		auto OnWindowCloseEvent(WindowCloseEvent& event, Window* window) -> void;
	private:
		ApplicationCommandLineArgs m_CommandLineArgs;
		std::vector<Scope<Window>> m_Windows;
		LayerStack m_LayerStack;
		ImGuiOverlay* m_ImGuiOverlay{};
		EventThread m_EventThread;

		// Flags
		bool m_Running : 1 {true};
	private:
		friend auto Main(int argc, char* argv[]) -> int;
		auto Run() -> void;
	};
}
