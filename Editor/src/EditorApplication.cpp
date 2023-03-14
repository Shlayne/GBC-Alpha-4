#include "EditorApplication.h"
#include "GBC/Core/EntryPoint.h"
#include "EditorLayer.h"

namespace gbc
{
	EditorApplication::EditorApplication(ApplicationInfo applicationInfo)
		: Application{applicationInfo}
	{
		WindowInfo windowInfo;
		windowInfo.width = 1600;
		windowInfo.height = 900;
		windowInfo.title = "GBC Editor";
		windowInfo.vsync = true;
		Window& window{OpenWindow(windowInfo)};
		PushLayer(new EditorLayer{});
	}

	auto CreateApplication(ApplicationCommandLineArgs commandLineArgs) -> Application*
	{
		ApplicationInfo applicationInfo;
		applicationInfo.commandLineArgs = commandLineArgs;
		applicationInfo.closeOnLastWindowClosed = true;
		Application* application{new EditorApplication{applicationInfo}};
		application->PushImGuiOverlay();
		return application;
	}
}
