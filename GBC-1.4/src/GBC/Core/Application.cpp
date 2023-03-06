#include "gbcpch.h"
#include "Application.h"

namespace gbc
{
	ApplicationCommandLineArgs::ApplicationCommandLineArgs(int argc, char** argv)
		: m_Count{argc}
		, m_Args{argv}
	{

	}

	auto ApplicationCommandLineArgs::operator[](size_t index) noexcept -> char*
	{
		return m_Args[index];
	}

	Application* s_ApplicationInstance = nullptr;

	Application::Application(ApplicationCommandLineArgs args)
		: m_CommandLineArgs{args}
	{
		// TODO: assert s_ApplicationInstance is nullptr
		s_ApplicationInstance = this;
	}

	Application::~Application()
	{

	}

	auto Application::Get() -> Application&
	{
		return *s_ApplicationInstance;
	}

	auto Application::GetCommandLineArgs() -> ApplicationCommandLineArgs
	{
		return m_CommandLineArgs;
	}

	auto Application::OnWindowCloseEvent(WindowCloseEvent& event) -> void
	{

	}

	auto Application::Run() -> void
	{
		while (true)
		{

		}
	}
}
