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
	}

	Application::~Application()
	{
		GBC_CORE_ASSERT(s_ApplicationInstance, "Tried to redestroy Application.");
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
		Window& window = *m_Windows.emplace_back(Window::CreateScope(info));
		window.SetEventCallback(GBC_BIND_FUNC(OnEvent));
		return window;
	}

	auto Application::PushLayer(Window& window, Layer* layer) -> void
	{
		LayerStack& layerStack{window.GetLayerStack()};
		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	auto Application::PopLayer(Window& window) -> Layer*
	{
		LayerStack& layerStack{window.GetLayerStack()};
		Layer* layer{layerStack.PopLayer()};
		layer->OnAttach();
		return layer;
	}

	auto Application::PushOverlay(Window& window, Layer* overlay) -> void
	{
		LayerStack& layerStack{window.GetLayerStack()};
		layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	auto Application::PopOverlay(Window& window) -> Layer*
	{
		LayerStack& layerStack{window.GetLayerStack()};
		Layer* overlay{layerStack.PopOverlay()};
		overlay->OnAttach();
		return overlay;
	}

	auto Application::OnEvent(Event& event, Window* window) -> void
	{
		if (!event.IsApplicationOnly())
		{
			GBC_CORE_ASSERT(window, "window == nullptr");
			auto& layerStack = window->GetLayerStack();
			for (auto it = layerStack.rbegin(); !event.IsHandled() && it != layerStack.rend(); ++it)
				(*it)->OnEvent(event);
		}
		event.Dispatch(this, &Application::OnWindowCloseEvent, window);
	}

	auto Application::OnWindowCloseEvent(WindowCloseEvent& event, Window* window) -> void
	{
		GBC_CORE_ASSERT(window, "window == nullptr");
		auto it = std::find_if(m_Windows.begin(), m_Windows.end(), [window](const Scope<Window>& w) -> bool { return w.get() == window; });
		GBC_CORE_ASSERT(it != m_Windows.end(), "it == m_Windows.end()");
		m_Windows.erase(it);

		if (m_Windows.empty() && m_CloseOnLastWindowClosed)
			Close();
	}

	auto Application::Run() -> void
	{
		while (m_Running)
		{
			for (auto& window : m_Windows)
				for (auto& layer : window->GetLayerStack())
					layer->OnUpdate(0.0f); // TODO: timestep

			for (auto& window : m_Windows)
				window->SwapBuffers();
			if (!m_Windows.empty()) // TODO: move poll events to its own file.
				m_Windows.front()->PollEvents();
		}
	}
}
