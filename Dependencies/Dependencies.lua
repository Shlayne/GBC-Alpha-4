IncludeDir = {}
LibraryDir = {}
Library = {}

-- Include Directories
	-- Header and Source; they have their own project.
	IncludeDir["glfw"] = "%{wks.location}/GBC/Dependencies/glfw-3.3.8/include"
	IncludeDir["glad"] = "%{wks.location}/GBC/Dependencies/glad-0.1.35/include"
	IncludeDir["imgui"] = "%{wks.location}/GBC/Dependencies/imgui-docking-wip-1.89.4"
	IncludeDir["spdlog"] = "%{wks.location}/GBC/Dependencies/spdlog-1.11.0/include"

	-- Header-Only; they don't have their own project.

	-- Header and Lib; they also don't have their own project.

-- Library Directories
--	LibraryDir["__LIBRARY_DIR_NAME__"] = "%{__LIBRARY_DIR_NAME__}/__LIBRARY_DIR_PATH__"

-- Libraries
--	Library["__LIBRARY_NAME__"] = "%{LibraryDir.__LIBRARY_NAME__}/__LIBRARY_PATH__"
