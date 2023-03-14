#pragma once

#include "GBC/Core/Layer.h"
#include <vector>

namespace gbc
{
	class LayerStack
	{
	public:
		auto PushLayer(Layer* layer) -> void;
		auto PopLayer() -> Layer*;
		auto PushOverlay(Layer* overlay) -> void;
		auto PopOverlay() -> Layer*;
	public:
		constexpr auto begin()         noexcept -> std::vector<Layer*>::iterator               { return m_Layers.begin();   }
		constexpr auto end()           noexcept -> std::vector<Layer*>::iterator               { return m_Layers.end();     }
		constexpr auto rbegin()        noexcept -> std::vector<Layer*>::reverse_iterator       { return m_Layers.rbegin();  }
		constexpr auto rend()          noexcept -> std::vector<Layer*>::reverse_iterator       { return m_Layers.rend();    }
		constexpr auto cbegin()  const noexcept -> std::vector<Layer*>::const_iterator         { return m_Layers.cbegin();  }
		constexpr auto cend()    const noexcept -> std::vector<Layer*>::const_iterator         { return m_Layers.cend();    }
		constexpr auto crbegin() const noexcept -> std::vector<Layer*>::const_reverse_iterator { return m_Layers.crbegin(); }
		constexpr auto crend()   const noexcept -> std::vector<Layer*>::const_reverse_iterator { return m_Layers.crend();   }
		constexpr auto begin()   const noexcept -> std::vector<Layer*>::const_iterator         { return m_Layers.begin();   }
		constexpr auto end()     const noexcept -> std::vector<Layer*>::const_iterator         { return m_Layers.end();     }
		constexpr auto rbegin()  const noexcept -> std::vector<Layer*>::const_reverse_iterator { return m_Layers.rbegin();  }
		constexpr auto rend()    const noexcept -> std::vector<Layer*>::const_reverse_iterator { return m_Layers.rend();    }
	private:
		std::vector<Layer*> m_Layers;
		size_t m_LayerEndIndex{0};
	};
}
