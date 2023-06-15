#include "gbcpch.h"
#include "Application.h"

namespace gbc
{
	Application* s_ApplicationInstance = nullptr;

	Application::Application(const ApplicationInfo& info)
		: m_CommandLineArgs{info.commandLineArgs}
	{
		GBC_CORE_ASSERT(!s_ApplicationInstance, "Tried to recreate Application.");
		s_ApplicationInstance = this;

		System::Init();
		m_EventThread.SetEventCallback(GBC_BIND_CLASS_FUNC(OnEvent));
		OpenWindow(info.primaryWindowInfo);

		m_ImGuiOverlay = new ImGuiOverlay{};
		PushOverlay(m_ImGuiOverlay);
	}

	Application::~Application()
	{
		GBC_CORE_ASSERT(s_ApplicationInstance, "Tried to redestroy Application.");

		// Destroy all layers.
		for (Layer* layer : m_LayerStack)
		{
			layer->OnDetach();
			delete layer;
		}

		// Destroy all windows explicitly before System::Shutdown.
		m_Windows.clear();

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
		window.SetEventCallback(GBC_BIND_MEMBER_FUNC(m_EventThread, EnqueueEvent));
		return window;
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
		for (auto it{m_LayerStack.rbegin()}; !event.IsHandled() && it != m_LayerStack.rend(); ++it)
		{
			Layer* layer{*it};
			if (layer->IsEnabled())
				layer->OnEvent(event);
		}

		event.Dispatch(this, &Application::OnWindowCloseEvent, window);
		// TODO: dont render on minimized windows.
	}

	auto Application::OnWindowCloseEvent(WindowCloseEvent& event, Window* window) -> void
	{
		GBC_CORE_ASSERT(window, "window == nullptr");
		window->Close();
	}

	auto Application::Run() -> void
	{
		while (m_Running && !m_Windows.empty())
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

				System::PollEvents();

				// Remove all windows that should close.
				std::erase_if(m_Windows, [](const Scope<Window>& window) { return window->ShouldClose(); });
			}
		}
	}
}
