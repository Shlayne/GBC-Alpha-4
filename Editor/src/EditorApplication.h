#pragma once

#include <GBC.h>

namespace gbc
{
	class EditorApplication : public Application
	{
	public:
		EditorApplication(ApplicationCommandLineArgs args);
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new EditorApplication(args);
	}
}
