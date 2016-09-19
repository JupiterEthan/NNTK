#include "Neuron.h"
#include "functional.h"

Neuron::Neuron()
{
	input = 0.0;
	output = 0.0;
	alpha = 0.0;
}

Neuron::Neuron(double output)
{
	input = 0.0;
	this->output = output;
	alpha = 0.0;
}

Neuron::Neuron(const Neuron& neuron)
{
	input = neuron.getInput();
	output = neuron.getOutput();
	alpha = neuron.getAlpha();
}

void Neuron::operator=(const Neuron& neuron)
{
	input = neuron.getInput();
	output = neuron.getOutput();
	alpha = neuron.getAlpha();
}

void Neuron::activate()
{
	output = sigmoid(input,alpha);
	
	return;
}

double Neuron::getInput()const
{
	return input;
}

void Neuron::setInput(double input)
{
	this->input = input;
	
	return;
}

double Neuron::getOutput()const
{
	return output;
}

double Neuron::getAlpha()const
{
	return alpha;
}

void Neuron::setAlpha(double alpha)
{
	this->alpha = alpha;
	
	return;
}
