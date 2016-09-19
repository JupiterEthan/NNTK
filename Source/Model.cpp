#include "Model.h"

Model::Model()
{
	numLayers = 0;
	layers = 0;
	weights = 0;
	bias = 0;
}

Model::Model(int numLayers)
{
	this->numLayers = numLayers;
	
	layers = new Layer[numLayers];
	weights = new Weights[numLayers];
	bias = new Bias[numLayers];
}

Model::Model(const Model& model)
{
	numLayers = model.getNumLayers();
	
	layers = new Layer[numLayers];
	for(int i=0;i<numLayers;i++)
	{
		layers[i] = model.layers[i];
	}
	
	weights = new Weights[numLayers];
	for(int i=0;i<numLayers;i++)
	{
		weights[i] = model.weights[i];
	}
	
	bias = new Bias[numLayers];
	for(int i=0;i<numLayers;i++)
	{
		bias[i] = model.bias[i];
	}
	
}

Model::~Model()
{
	delete[] layers;
	delete[] weights;
	delete[] bias;
}

void Model::operator=(const Model& model)
{
	delete[] layers;
	delete[] weights;
	delete[] bias;
	
	numLayers = model.getNumLayers();
	
	layers = new Layer[numLayers];
	for(int i=0;i<numLayers;i++)
	{
		layers[i] = model.layers[i];
	}
	
	weights = new Weights[numLayers];
	for(int i=0;i<numLayers;i++)
	{
		weights[i] = model.weights[i];
	}
	
	bias = new Bias[numLayers];
	for(int i=0;i<numLayers;i++)
	{
		bias[i] = model.bias[i];
	}
	
	return;
}

int Model::getNumLayers()const
{
	return numLayers;
}

void Model::setNumLayers(int numLayers)
{
	this->numLayers = numLayers;
	
	return;
}
