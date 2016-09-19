#include "Label.h"
#include <string.h>

Label::Label()
{
	size = 0;
	lb = 0;
}

Label::Label(int size)
{
	this->size = size;
	
	lb = new double[size];
}

Label::Label(const Label& label)
{
	size = label.getSize();
	
	lb = new double[size];
	memcpy(lb,label.lb,size*sizeof(double));
}

Label::~Label()
{
	delete[] lb;
}

void Label::operator=(const Label& label)
{
	delete[] lb;
	
	size = label.getSize();
	lb = new double[size];
	memcpy(lb,label.lb,size*sizeof(double));
	
	return;
}

int Label::getSize()const
{
	return size;
}
