#pragma once

class Instance
{
	private:
		int dim;
		int size;
	
	public:
		double* ins;
		
		Instance();
		Instance(int size,int dim);
		Instance(const Instance& instance);
		
		~Instance();
		
		void operator=(const Instance& instance);
		
		int getDim()const;
		int getSize()const;
};
