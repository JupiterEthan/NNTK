#include "Instance.h"
#include <string.h>

Instance::Instance()
{
	dim = 0;
	size = 0;
	ins = 0;
}

Instance::Instance(int size,int dim)
{
	this->size = size;
	this->dim = dim;
	
	ins = new double[dim*size];
}

Instance::Instance(const Instance& instance)
{
	dim = instance.getDim();
	size = instance.getSize();
	
	ins = new double[dim*size];
	memcpy(ins,instance.ins,dim*size*sizeof(double));
}

Instance::~Instance()
{
	delete[] ins;
}

void Instance::operator=(const Instance& instance)
{
	dim = instance.getDim();
	size = instance.getSize();
	
	delete[] ins;
	ins = new double[dim*size];
	memcpy(ins,instance.ins,dim*size*sizeof(double));
}

int Instance::getDim()const
{
	return dim;
}

int Instance::getSize()const
{
	return size;
}
