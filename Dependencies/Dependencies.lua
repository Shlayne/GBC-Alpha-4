IncludeDir = {}
LibraryDir = {}
Library = {}

-- Include Directories
	-- Header and Source; they have their own project.
	IncludeDir["glfw"] = "%{wks.location}/GBC-1.4/Dependencies/glfw-3.3.8/include"
	IncludeDir["spdlog"] = "%{wks.location}/GBC-1.4/Dependencies/spdlog-1.11.0/include"

	-- Header-Only; they don't have their own project.

	-- Header and Lib; they also don't have their own project.

-- Library Directories
--	LibraryDir["__LIBRARY_DIR_NAME__"] = "%{__LIBRARY_DIR_NAME__}/__LIBRARY_DIR_PATH__"

-- Libraries
--	Library["__LIBRARY_NAME__"] = "%{LibraryDir.__LIBRARY_NAME__}/__LIBRARY_PATH__"
