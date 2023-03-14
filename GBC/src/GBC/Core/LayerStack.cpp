#include "gbcpch.h"
#include "LayerStack.h"

namespace gbc
{
	auto LayerStack::PushLayer(Layer* layer) -> void
	{
		GBC_CORE_ASSERT(layer, "layer == nullptr");
		GBC_CORE_ASSERT(std::find(m_Layers.begin(), m_Layers.end(), layer) == m_Layers.end(), "Tried to add the same layer twice.");

		m_Layers.insert(m_Layers.begin() + m_LayerEndIndex, layer);
		++m_LayerEndIndex;
	}

	auto LayerStack::PopLayer() -> Layer*
	{
		GBC_CORE_ASSERT(0 < m_LayerEndIndex, "Tried to pop a layer when none were present.");

		--m_LayerEndIndex;
		auto layerIt{m_Layers.begin() + m_LayerEndIndex};
		Layer* layer{*layerIt};
		m_Layers.erase(layerIt);
		return layer;
	}

	auto LayerStack::PushOverlay(Layer* overlay) -> void
	{
		GBC_CORE_ASSERT(overlay, "layer == nullptr");
		GBC_CORE_ASSERT(std::find(m_Layers.begin(), m_Layers.end(), overlay) == m_Layers.end(), "Tried to add the same overlay twice.");

		m_Layers.push_back(overlay);
	}

	auto LayerStack::PopOverlay() -> Layer*
	{
		GBC_CORE_ASSERT(m_LayerEndIndex < m_Layers.size(), "Tried to pop an overlay when none were present.");

		Layer* overlay{m_Layers.back()};
		m_Layers.pop_back();
		return overlay;
	}
}
