#include "GBC/Core/Application.h"
#include "GBC/Core/Logger.h"

namespace gbc
{
	extern auto CreateApplication(ApplicationCommandLineArgs args) -> Application*;

	auto Main(int argc, char** argv) -> int
	{
		Logger::Create();

		Application* application = CreateApplication({argc, argv});
		application->Run();
		delete application;

		return 0;
	}
}

#if GBC_SYSTEM_WINDOWS

#if GBC_CONFIG_DIST

#include <Windows.h>

auto APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hInstPrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) -> int
{
	static_cast<void>(hInst, hInstPrev, lpCmdLine, nCmdShow);
	return gbc::Main(__argc, __argv);
}

#else // !GBC_CONFIG_DIST

auto main(int argc, char** argv) -> int
{
	return gbc::Main(argc, argv);
}

#endif // GBC_CONFIG_DIST

#else // !GBC_SYSTEM_WINDOWS
#error System currently not supported.
#endif // GBC_SYSTEM_WINDOWS
