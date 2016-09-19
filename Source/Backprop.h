#pragma once

#include "Delta.h"
#include "Model.h"

class Backprop
{
	private:
		int numLayers;
		
	public:
		Delta* delta;
		
		Backprop();
		Backprop(const Model& model,double d,double alpha);
		Backprop(const Backprop& backprop);
		
		~Backprop();
		
		void operator=(const Backprop& backprop);
		
		int getNumLayers()const;
		void setNumLayers(int numLayers);
};
