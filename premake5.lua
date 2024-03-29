include "Dependencies/premake/Custom/solutionitems.lua"

workspace "GBC-Alpha-4"
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

group "Dependencies/GBC"
	include "GBC/Dependencies/imgui-docking-wip-1.89.4"
	include "GBC/Dependencies/stb-2.28"
group "Dependencies/GBC/Platform"
	filter "system:windows"
		include "GBC/Dependencies/glfw-3.3.8"
		include "GBC/Dependencies/glad-0.1.35"
	filter ""
group "Dependencies/Editor"

group ""

include "GBC"
include "Editor"
