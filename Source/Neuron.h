#pragma once

class Neuron
{
	private:
		double input;
		double output;
		double alpha;
	public:
		Neuron();
		Neuron(double output);
		Neuron(const Neuron& neuron);
		
		void operator=(const Neuron& neuron);
		
		void activate();
		double getInput()const;
		void setInput(double input);
		double getOutput()const;
		double getAlpha()const;
		void setAlpha(double alpha);
};
