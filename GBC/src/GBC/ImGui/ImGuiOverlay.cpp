#include "gbcpch.h"
#include "GBC/Core/Application.h"
#include "ImGuiOverlay.h"
#include "GBC/Core/Window.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <glfw/glfw3.h>

namespace gbc
{
	auto ImGuiOverlay::OnAttach() -> void
	{
		// TODO: profile function

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io{ImGui::GetIO()};
		ImGuiStyle& style{ImGui::GetStyle()};

		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable;
		io.ConfigWindowsMoveFromTitleBarOnly = true;

		style.WindowRounding = 0.0f;
		style.FramePadding = {4.0f, 4.0f};
		style.WindowPadding = {4.0f, 4.0f};
		style.WindowMenuButtonPosition = ImGuiDir_None;

		// Dark theme
		ImGui::StyleColorsDark();
		auto& colors{style.Colors};

		// Window
		colors[ImGuiCol_WindowBg]           = {0.100f, 0.105f, 0.110f, 1.000f};

		// Frame Background
		colors[ImGuiCol_FrameBg]            = {0.165f, 0.170f, 0.175f, 1.000f};
		colors[ImGuiCol_FrameBgHovered]     = {0.200f, 0.205f, 0.210f, 1.000f};
		colors[ImGuiCol_FrameBgActive]      = {0.150f, 0.155f, 0.160f, 1.000f};

		// Title Background
		colors[ImGuiCol_TitleBg]            = {0.150f, 0.155f, 0.160f, 1.000f};
		colors[ImGuiCol_TitleBgActive]      = {0.150f, 0.155f, 0.160f, 1.000f};
		colors[ImGuiCol_TitleBgCollapsed]   = {0.150f, 0.155f, 0.160f, 1.000f};
		
		// Checkbox
		colors[ImGuiCol_CheckMark]          = {0.260f, 0.590f, 0.980f, 1.000f};

		// Slider
		colors[ImGuiCol_SliderGrab]         = {0.338f, 0.338f, 0.338f, 1.000f};
		colors[ImGuiCol_SliderGrabActive]   = {0.338f, 0.338f, 0.338f, 1.000f};

		// Buttons
		colors[ImGuiCol_Button]             = {0.200f, 0.205f, 0.210f, 1.000f};
		colors[ImGuiCol_ButtonHovered]      = {0.300f, 0.305f, 0.310f, 1.000f};
		colors[ImGuiCol_ButtonActive]       = {0.150f, 0.155f, 0.160f, 1.000f};

		// Headers
		colors[ImGuiCol_Header]             = {0.200f, 0.205f, 0.210f, 1.000f};
		colors[ImGuiCol_HeaderHovered]      = {0.300f, 0.305f, 0.310f, 1.000f};
		colors[ImGuiCol_HeaderActive]       = {0.150f, 0.155f, 0.160f, 1.000f};

		// Tabs
		colors[ImGuiCol_Tab]                = {0.150f, 0.155f, 0.160f, 1.000f};
		colors[ImGuiCol_TabHovered]         = {0.380f, 0.385f, 0.390f, 1.000f};
		colors[ImGuiCol_TabActive]          = {0.280f, 0.285f, 0.290f, 1.000f};
		colors[ImGuiCol_TabUnfocused]       = {0.150f, 0.155f, 0.160f, 1.000f};
		colors[ImGuiCol_TabUnfocusedActive] = {0.200f, 0.205f, 0.210f, 1.000f};

		// Drag/Drop
		colors[ImGuiCol_DragDropTarget]     = {0.102f, 0.337f, 0.608f, 1.000f};

		auto& window{Application::Get().GetWindow()};
		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(window.GetNativeWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	auto ImGuiOverlay::OnDetach() -> void
	{
		// TODO: profile function

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	auto ImGuiOverlay::OnEvent(Event& event) -> void
	{
		ImGuiIO& io{ImGui::GetIO()};
		if (m_BlockingEvents && ((event.IsKeyEvent() && io.WantCaptureKeyboard) || (event.IsMouseEvent() && io.WantCaptureMouse)))
			event.Handle();
	}

	auto ImGuiOverlay::Begin() -> void
	{
		// TODO: profile function

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	auto ImGuiOverlay::End() -> void
	{
		// TODO: profile function

		ImGuiIO& io{ImGui::GetIO()};
		auto& window{Application::Get().GetWindow()};
		io.DisplaySize = {static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight())};

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLFWwindow* backupContext{glfwGetCurrentContext()};
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backupContext);
	}
}
