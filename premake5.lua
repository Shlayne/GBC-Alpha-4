include "Dependencies/premake/Custom/solutionitems.lua"

workspace "GBC-1.4"
	architecture "x86_64"
	startproject "Editor"

	configurations { "Profile", "Debug", "Release", "Dist" }

	solutionitems {
		-- Visual Studio
		".editorconfig",

		-- Git
		".gitignore",
		".gitattributes",

		-- Scripts
		"Scripts/GenerateProjects.bat",

		-- Lua Scripts
		"premake5.lua",
		"Dependencies/Dependencies.lua",
		"Dependencies/premake/Custom/solutionitems.lua",
		"Dependencies/premake/Custom/notyetimplemented.lua",
		
		-- Misc
		"README.md"
	}

	flags {
		"MultiProcessorCompile"
	}

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Dependencies/premake/Custom/notyetimplemented.lua"
include "Dependencies/Dependencies.lua"

group "Dependencies/GBC-1.4/Platform"
	filter "system:windows"
		include "GBC-1.4/Dependencies/glfw-3.3.8"
		include "GBC-1.4/Dependencies/glad-0.1.35"
	filter ""
group "Dependencies/Editor"

group ""

include "GBC-1.4"
include "Editor"
