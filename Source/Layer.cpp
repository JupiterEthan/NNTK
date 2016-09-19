#include "Layer.h"

Layer::Layer()
{
	size = 0;
	neurons = 0;
}

Layer::Layer(int size)
{
	this->size = size;
	neurons = new Neuron[size];
}

Layer::Layer(const Layer& layer)
{
	size = layer.getSize();
	
	neurons = new Neuron[size];
	
	for(int i=0;i<size;i++)
	{
		neurons[i] = layer.neurons[i];
	}
}

Layer::~Layer()
{
	delete[] neurons;
}

void Layer::operator=(const Layer& layer)
{
	delete[] neurons;
	
	size = layer.getSize();
	
	neurons = new Neuron[size];
	
	for(int i=0;i<size;i++)
	{
		neurons[i] = layer.neurons[i];
	}
}

int Layer::getSize()const
{
	return size;
}
