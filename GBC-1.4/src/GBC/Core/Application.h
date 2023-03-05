#pragma once

#include "GBC/Core/Core.h"

namespace gbc
{
	class ApplicationCommandLineArgs
	{
	public:
		ApplicationCommandLineArgs() noexcept = default;
		ApplicationCommandLineArgs(int argc, char** argv);
	public:
		char* operator[](size_t index) noexcept;
	private:
		int m_Count{0};
		char** m_Args{nullptr};
	};

	class Application
	{
	public:
		Application(ApplicationCommandLineArgs args);
		virtual ~Application();
	public:
		static Application& Get();
	public:
		ApplicationCommandLineArgs GetCommandLineArgs();
	private:
		ApplicationCommandLineArgs m_CommandLineArgs;
	private:
		friend int Main(int argc, char** argv);
		void Run();
	};
}
