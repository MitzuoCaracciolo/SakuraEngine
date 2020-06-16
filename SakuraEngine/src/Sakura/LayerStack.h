#pragma once
#include "Sakura/skpch.h"
#include "Sakura/Core.h"
#include "Sakura/Layer.h"

namespace Sakura
{
	class SAKURA_API LayerStack 
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushLayerOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopLayerOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator  m_LayerInsert;
	};
}

