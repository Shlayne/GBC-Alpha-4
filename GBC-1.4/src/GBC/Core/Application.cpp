#include "gbcpch.h"
#include "Application.h"

namespace gbc
{
	ApplicationCommandLineArgs::ApplicationCommandLineArgs(int argc, char** argv)
		: m_Count{argc}
		, m_Args{argv}
	{

	}

	auto ApplicationCommandLineArgs::operator[](size_t index) const noexcept -> const char*
	{
		return m_Args[index];
	}

	Application* s_ApplicationInstance = nullptr;

	Application::Application(const ApplicationInfo& info)
		: m_CommandLineArgs{info.args}
	{
		GBC_CORE_ASSERT(!s_ApplicationInstance, "Tried to recreate Application.");
		s_ApplicationInstance = this;
	}

	Application::~Application()
	{

	}

	auto Application::Get() -> Application&
	{
		return *s_ApplicationInstance;
	}

	auto Application::GetWindow(size_t index) -> Window&
	{
		GBC_CORE_ASSERT(index < m_Windows.size(), "Tried to get a non-existent window.");
		return *m_Windows[index];
	}

	auto Application::OpenWindow(const WindowInfo& info) -> Window&
	{
		Window& window = *m_Windows.emplace_back(Window::CreateScope(info));
		window.SetEventCallback(GBC_BIND_FUNC(OnEvent));
		return window;
	}

	auto Application::OnEvent(Event& event, Window* window) -> void
	{
		event.Dispatch(this, &Application::OnWindowCloseEvent, window);
	}

	auto Application::OnWindowCloseEvent(WindowCloseEvent& event, Window* window) -> void
	{

	}

	auto Application::Run() -> void
	{
		GBC_CORE_ASSERT(!m_Running, "Tried to rerun the Application.");
		m_Running = true;

		while (m_Running)
		{
			for (auto& window : m_Windows)
				window->SwapBuffers();
		}
	}
}
