project "imgui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
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
		"%{IncludeDir.glfw}",
		"%{IncludeDir.imgui}"
	}

	filter "system:windows"
		systemversion "latest"

		files {
			"backends/imgui_impl_opengl3.cpp",
			"backends/imgui_impl_glfw.cpp",
		}

		defines {
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Profile"
		runtime "Debug"
		optimize "Off"
		symbols "On"

	filter "configurations:Debug"
		runtime "Debug"
		optimize "Debug"
		symbols "Full"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "Full"
		symbols "Off"
