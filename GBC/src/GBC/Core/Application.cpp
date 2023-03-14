#include "gbcpch.h"
#include "Application.h"

namespace gbc
{
	ApplicationCommandLineArgs::ApplicationCommandLineArgs(int argc, char** argv)
		: m_Count{argc}
		, m_Args{argv}
	{

	}

	auto ApplicationCommandLineArgs::operator[](size_t index) const noexcept -> const char*
	{
		return m_Args[index];
	}

	Application* s_ApplicationInstance = nullptr;

	Application::Application(const ApplicationInfo& info)
		: m_CommandLineArgs{info.commandLineArgs}
		, m_CloseOnLastWindowClosed{info.closeOnLastWindowClosed}
	{
		GBC_CORE_ASSERT(!s_ApplicationInstance, "Tried to recreate Application.");
		s_ApplicationInstance = this;

		System::Init();
	}

	Application::~Application()
	{
		GBC_CORE_ASSERT(s_ApplicationInstance, "Tried to redestroy Application.");

		System::Shutdown();

		s_ApplicationInstance = nullptr;
	}

	auto Application::Get() -> Application&
	{
		return *s_ApplicationInstance;
	}

	auto Application::GetWindow(size_t index) -> Window&
	{
		GBC_CORE_ASSERT(index < m_Windows.size(), "Tried to get a non-existent window.");
		return *m_Windows[index];
	}

	auto Application::OpenWindow(const WindowInfo& info) -> Window&
	{
		Window& window{*m_Windows.emplace_back(Window::CreateScope(info))};
		window.SetEventCallback(GBC_BIND_FUNC(OnEvent));
		return window;
	}

	auto Application::PushImGuiOverlay() -> void
	{
		GBC_CORE_ASSERT(!m_ImGuiOverlay, "Tried to repush ImGuiOverlay.");

		m_ImGuiOverlay = new ImGuiOverlay{};
		PushOverlay(m_ImGuiOverlay);
	}

	auto Application::PushLayer(Layer* layer) -> void
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	auto Application::PopLayer() -> Layer*
	{
		Layer* layer{m_LayerStack.PopLayer()};
		layer->OnDetach();
		return layer;
	}

	auto Application::PushOverlay(Layer* overlay) -> void
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	auto Application::PopOverlay() -> Layer*
	{
		Layer* overlay{m_LayerStack.PopOverlay()};
		overlay->OnDetach();
		return overlay;
	}

	auto Application::OnEvent(Event& event, Window* window) -> void
	{
		GBC_CORE_ASSERT(window, "window == nullptr");

		for (auto it{m_LayerStack.rbegin()}; !event.IsHandled() && it != m_LayerStack.rend(); ++it)
		{
			Layer* layer{*it};
			if (layer->IsEnabled())
				layer->OnEvent(event);
		}

		event.Dispatch(this, &Application::OnWindowCloseEvent, window);
	}

	auto Application::OnWindowCloseEvent(WindowCloseEvent& event, Window* window) -> void
	{
		GBC_CORE_ASSERT(window, "window == nullptr");
		window->Close();
	}

	auto Application::Run() -> void
	{
		while (m_Running)
		{
			Timestep timestep{System::GetTimestep()};

			// Update all enabled layers.
			for (Layer* layer : m_LayerStack)
				if (layer->IsEnabled())
					layer->OnUpdate(timestep);

			if (!m_Windows.empty())
			{
				if (m_ImGuiOverlay)
				{
					// Render ImGui for all enabled layers.
					m_ImGuiOverlay->Begin();
					for (Layer* layer : m_LayerStack)
						if (layer->IsEnabled())
							layer->OnImGuiRender();
					m_ImGuiOverlay->End();
				}

				// Update window buffers.
				for (auto& window : m_Windows)
					window->SwapBuffers();

				// Poll events.
				System::PollEvents();

				// Remove all windows that should close.
				std::erase_if(m_Windows, [](const Scope<Window>& window) { return window->ShouldClose(); });
			}

			// Close the application if applicable.
			if (m_CloseOnLastWindowClosed && m_Windows.empty())
				Close();
		}

		// Destroy all layers.
		for (Layer* layer : m_LayerStack)
		{
			layer->OnDetach();
			delete layer;
		}
	}
}
