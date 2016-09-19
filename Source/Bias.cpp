#include "Bias.h"
#include <string.h>

Bias::Bias()
{
	size = 0;
	b = 0;
}

Bias::Bias(int size)
{
	this->size = size;
	
	b = new double[size];
}

Bias::Bias(const Bias& bias)
{
	size = bias.getSize();
	
	b = new double[size];
	
	memcpy(b,bias.b,size*sizeof(double));
}

Bias::~Bias()
{
	delete[] b;
}

void Bias::operator=(const Bias& bias)
{
	delete[] b;
	
	size = bias.getSize();
	
	b = new double[size];
	
	memcpy(b,bias.b,size*sizeof(double));
	
	return;
}

int Bias::getSize()const
{
	return size;
}

void Bias::setSize(int size)
{
	this->size = size;
	
	return;
}

