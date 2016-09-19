#pragma once

#include "Neuron.h"

class Layer
{
	private:
		int size;
		
	public:
		Neuron* neurons;
		
		Layer();
		Layer(int size);
		Layer(const Layer& layer);
		
		~Layer();
		
		void operator=(const Layer& layer);
		
		int getSize()const;
};
