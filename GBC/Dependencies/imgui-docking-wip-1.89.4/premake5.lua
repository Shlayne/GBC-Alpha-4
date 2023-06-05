project "imgui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

	files {
		"imconfig.h",
		"imgui.cpp",
		"imgui.h",
		"imgui_demo.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_tables.cpp",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h"
	}

	includedirs {
		"%{wks.location}/GBC/src",

		"%{IncludeDir.imgui}",

		"%{IncludeDir.spdlog}"
	}

	filter "system:windows"
		systemversion "latest"
		usestdpreproc "On" -- msvc doesn't provide __VA_OPT__ by default; this fixes that.
		buildoptions "/wd5105" -- This must be here to prevent a warning produced at WinBase.h:9528.

		files {
			"backends/imgui_impl_opengl3.cpp",
			"backends/imgui_impl_glfw.cpp"
		}

		includedirs {
			"%{IncludeDir.glfw}"
		}

		defines {
			"GBC_SYSTEM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS"
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
