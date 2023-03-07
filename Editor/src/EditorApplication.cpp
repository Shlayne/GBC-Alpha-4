#include "EditorApplication.h"
#include "GBC/Core/EntryPoint.h"

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
		OpenWindow(windowInfo);
	}

	auto CreateApplication(ApplicationCommandLineArgs args) -> Application*
	{
		ApplicationInfo applicationInfo;
		applicationInfo.args = args;
		return new EditorApplication{applicationInfo};
	}
}
