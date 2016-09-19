#pragma once

#include "Layer.h"
#include "Weights.h"
#include "Bias.h"

class Model
{
	private:
		int numLayers;
		
	public:	
		Layer* layers;
		Weights* weights;
		Bias* bias;
		
		Model();
		Model(int numLayers);
		Model(const Model& model);
		
		~Model();
		
		void operator=(const Model& model);
		
		int getNumLayers()const;
		void setNumLayers(int numLayers);
};
