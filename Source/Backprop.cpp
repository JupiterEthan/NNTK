#include "Backprop.h"
#include "Label.h"
#include "functional.h"

Backprop::Backprop()
{
	numLayers = 0;
	delta = 0;
}

Backprop::Backprop(const Backprop& backprop)
{
	numLayers = backprop.getNumLayers();
	
	delta = new Delta[numLayers];
	for(int i=0;i<numLayers;i++)
	{
		delta[i] = backprop.delta[i];
	}
}

Backprop::Backprop(const Model& model,double d,double alpha)
{
	numLayers = model.getNumLayers();
	
	delta = new Delta[numLayers];
	
	for(int i=0;i<numLayers;i++)
	{
		delta[i].del = new double[(model.layers[i]).getSize()];
		delta[i].setSize((model.layers[i]).getSize());
	}
	
	for(int i=numLayers-1;i>=0;i--)
	{
		for(int j=0;j<(model.layers[i]).getSize();j++)
		{
			if(i == numLayers-1)
			{
				double y = ((model.layers[i]).neurons[0]).getOutput();
				
				delta[i].del[0] = alpha*y*(1.0-y)*(d-y);
			}
			else
			{
				double y = ((model.layers[i]).neurons[j]).getOutput();
				
				delta[i].del[j] = alpha*y*(1.0-y)*innerProduct((model.weights[i+1]).w+j*(model.weights[i+1]).getPostSize(),delta[i+1].del,delta[i+1].getSize());
			}
		}
	}
	
	return;
}

Backprop::~Backprop()
{
	delete[] delta;
}

void Backprop::operator=(const Backprop& backprop)
{
	delete[] delta;
	
	numLayers = backprop.getNumLayers();
	
	delta = new Delta[numLayers];
	for(int i=0;i<numLayers;i++)
	{
		delta[i] = backprop.delta[i];
	}
	
	return;
}

int Backprop::getNumLayers()const
{
	return numLayers;
}

void Backprop::setNumLayers(int numLayers)
{
	this->numLayers = numLayers;
	
	return;
}
