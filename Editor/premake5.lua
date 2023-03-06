project "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	cdialect "C17"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

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
		"%{wks.location}/GBC-1.4/src",

		-- Add any dependency includes here.
		"%{IncludeDir.spdlog}",
	}
	
	-- Add any links dependency libs via their project names here.
	links {
		"GBC-1.4"
	}

	filter "system:windows"
		systemversion "latest"
		usestdpreproc "On" -- msvc doesn't provide __VA_OPT__ by default; this fixes that.
		buildoptions "/wd5105" -- Until Microsoft updates Windows 10 to not have terrible code (aka never), this must be here to prevent a warning.
		defines "GBC_SYSTEM_WINDOWS"

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
		kind "WindowedApp"
		runtime "Release"
		optimize "Full"
		symbols "Off"
		defines "GBC_CONFIG_DIST"
