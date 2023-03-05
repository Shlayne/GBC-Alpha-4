#include "Application.h"

namespace gbc
{
	ApplicationCommandLineArgs::ApplicationCommandLineArgs(int argc, char** argv)
		: m_Count{argc}
		, m_Args{argv}
	{
	}

	char* ApplicationCommandLineArgs::operator[](size_t index) noexcept
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

	Application& Application::Get()
	{
		return *s_ApplicationInstance;
	}

	ApplicationCommandLineArgs Application::GetCommandLineArgs()
	{
		return m_CommandLineArgs;
	}

	void Application::Run()
	{
		while (true)
		{

		}
	}
}
