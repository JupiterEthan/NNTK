#include "Weights.h"
#include <string.h>

Weights::Weights()
{
	preSize = 0;
	postSize = 0;
	w = 0;
}

Weights::Weights(int preSize,int postSize)
{
	this->preSize = preSize;
	this->postSize = postSize;
	
	w = new double[preSize*postSize];
}

Weights::Weights(const Weights& weights)
{
	preSize = weights.getPreSize();
	postSize = weights.getPostSize();
	
	w = new double[preSize*postSize];
	
	memcpy(w,weights.w,preSize*postSize*sizeof(double));
}

Weights::~Weights()
{
	delete[] w;
}

void Weights::operator=(const Weights& weights)
{
	delete[] w;
	
	preSize = weights.getPreSize();
	postSize = weights.getPostSize();
	
	w = new double[preSize*postSize];
	
	memcpy(w,weights.w,preSize*postSize*sizeof(double));
	
	return;
}

int Weights::getPreSize()const
{
	return preSize;
}

void Weights::setPreSize(int preSize)
{
	this->preSize = preSize;
	
	return; 
}

int Weights::getPostSize()const
{
	return postSize;
}

void Weights::setPostSize(int postSize)
{
	this->postSize = postSize;
	
	return;
}


