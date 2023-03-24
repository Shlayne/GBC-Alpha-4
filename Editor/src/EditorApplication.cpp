#include "EditorApplication.h"
#include "GBC/Core/EntryPoint.h"
#include "EditorLayer.h"

namespace gbc
{
	EditorApplication::EditorApplication(const ApplicationInfo& info)
		: Application{info}
	{
		PushLayer(new EditorLayer{});
	}

	auto CreateApplication(ApplicationCommandLineArgs commandLineArgs) -> Application*
	{
		ApplicationInfo info;
		info.commandLineArgs = commandLineArgs;

		WindowInfo& windowInfo = info.primaryWindowInfo;
		windowInfo.width = 1600;
		windowInfo.height = 900;
		windowInfo.title = "GBC Editor";
		windowInfo.vsync = true;

		return new EditorApplication{info};
	}
}
