#include "EditorApplication.h"
#include "GBC/Core/EntryPoint.h"
#include "EditorLayer.h"

namespace gbc
{
	EditorApplication::EditorApplication(ApplicationInfo applicationInfo)
		: Application{applicationInfo}
	{
		PushLayer(new EditorLayer{});
	}

	auto CreateApplication(ApplicationCommandLineArgs commandLineArgs) -> Application*
	{
		ApplicationInfo applicationInfo;
		applicationInfo.commandLineArgs = commandLineArgs;

		WindowInfo& windowInfo = applicationInfo.primaryWindowInfo;
		windowInfo.width = 1600;
		windowInfo.height = 900;
		windowInfo.title = "GBC Editor";
		windowInfo.vsync = true;

		return new EditorApplication{applicationInfo};
	}
}
