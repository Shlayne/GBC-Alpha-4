#include "GBC/Core/Application.h"

namespace gbc
{
	extern Application* CreateApplication(ApplicationCommandLineArgs args);

	int Main(int argc, char** argv)
	{
		static_cast<void>(argc, argv);

		Application* application = CreateApplication({ argc, argv });
		application->Run();
		delete application;

		return 0;
	}
}

#if GBC_SYSTEM_WINDOWS

#if GBC_CONFIG_DIST

#include <Windows.h>

int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hInstPrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	static_cast<void>(hInst, hInstPrev, lpCmdLine, nCmdShow);
	return gbc::Main(__argc, __argv);
}

#else // !GBC_CONFIG_DIST

int main(int argc, char** argv)
{
	return gbc::Main(argc, argv);
}

#endif // GBC_CONFIG_DIST

#else // !GBC_SYSTEM_WINDOWS
#error System currently not supported.
#endif // GBC_SYSTEM_WINDOWS
