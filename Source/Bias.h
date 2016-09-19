#pragma once

class Bias
{
	private:
		int size;
	
	public:	
		double* b;
		
		Bias();
		Bias(int size);
		Bias(const Bias& bias);
		
		~Bias();
		
		void operator=(const Bias& bias);
		
		int getSize()const;
		void setSize(int size);
};
