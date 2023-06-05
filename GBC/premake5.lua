project "GBC"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	cdialect "C17"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

	pchheader "gbcpch.h"
	pchsource "src/gbcpch.cpp"

	files {
		"src/**.h",
		"src/**.c",
		"src/**.hpp",
		"src/**.cpp",
		"src/**.inl"
	}

	includedirs {
		-- Add any project source directories here.
		"src",
		-- "%{wks.location}/__PROJECT_NAME__/src",

		-- Add any dependency includes here.
		"%{IncludeDir.glad}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.stb}",

		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}"
	}
	
	-- Add any links dependency libs via their project names here.
	links {
		"imgui",
		"stb"
	}

	filter "system:windows"
		systemversion "latest"
		usestdpreproc "On" -- msvc doesn't provide __VA_OPT__ by default; this fixes that.
		buildoptions "/wd5105" -- This must be here to prevent a warning produced at WinBase.h:9528.
		defines "GBC_SYSTEM_WINDOWS"

		links {
			"glfw",
			"glad",
			"opengl32.lib"
		}

	filter "configurations:Profile"
		runtime "Debug"
		optimize "Off"
		symbols "On"
		defines "GBC_CONFIG_PROFILE"

	filter "configurations:Debug"
		runtime "Debug"
		optimize "Debug"
		symbols "Full"
		defines "GBC_CONFIG_DEBUG"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "On"
		defines "GBC_CONFIG_RELEASE"

	filter "configurations:Dist"
		runtime "Release"
		optimize "Full"
		symbols "Off"
		defines "GBC_CONFIG_DIST"

		-- These only have debug logging
		excludes "src/GBC/Event/*.cpp"

	filter "system:not windows"
		excludes "Platform/System/Windows/**"
