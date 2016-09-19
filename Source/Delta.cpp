#include "Delta.h"
#include <string.h>

Delta::Delta()
{
	size = 0;
	del = 0;
}

Delta::Delta(const Delta& delta)
{
	size = delta.getSize();
	del = new double[size];
	
	memcpy(del,delta.del,size*sizeof(double));
}

Delta::~Delta()
{
	delete[] del;
}

void Delta::operator=(const Delta& delta)
{
	delete[] del;
	
	size = delta.getSize();
	del = new double[size];
	
	memcpy(del,delta.del,size*sizeof(double));
	
	return;
}


int Delta::getSize()const
{
	return size;
}

void Delta::setSize(int size)
{
	this->size = size;
	
	return;
}
