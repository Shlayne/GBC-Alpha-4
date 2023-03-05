#pragma once

#include <GBC.h>

namespace gbc
{
	class EditorApplication : public Application
	{
	public:
		EditorApplication(ApplicationCommandLineArgs args);
	};

	auto CreateApplication(ApplicationCommandLineArgs args) -> Application*
	{
		return new EditorApplication(args);
	}
}
