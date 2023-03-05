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
		auto operator[](size_t index) noexcept -> char*;
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
		static auto Get() -> Application&;
	public:
		auto GetCommandLineArgs() -> ApplicationCommandLineArgs;
	private:
		ApplicationCommandLineArgs m_CommandLineArgs;
	private:
		friend auto Main(int argc, char** argv) -> int;
		auto Run() -> void;
	};
}
