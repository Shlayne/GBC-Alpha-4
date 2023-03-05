IncludeDir = {}
LibraryDir = {}
Library = {}

-- Include Directories
--	IncludeDir["__PROJECT_NAME__"] = "%{__PROJECT_DIR_NAME__}/__PROJECT_INCLUDE_PATH__"

	-- Header and Source; they have their own project.
	IncludeDir["spdlog"] = "%{wks.location}/GBC-1.4/Dependencies/spdlog-1.11.0/include"

	-- Header-Only; they don't have their own project.

	-- Header and Lib; they also don't have their own project.

-- Library Directories
--	LibraryDir["__LIBRARY_DIR_NAME__"] = "%{__LIBRARY_DIR_NAME__}/__LIBRARY_DIR_PATH__"

-- Libraries
--	Library["__LIBRARY_NAME__"] = "%{LibraryDir.__LIBRARY_NAME__}/__LIBRARY_PATH__"
