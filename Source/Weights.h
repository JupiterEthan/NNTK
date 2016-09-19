#pragma once

class Weights
{
	private:
		int preSize;
		int postSize;
	
	public:	
		double* w;
		
		Weights();
		Weights(int preSize,int postSize);
		Weights(const Weights& weights);
		
		~Weights();
		
		void operator=(const Weights& weights);
		
		int getPreSize()const;
		void setPreSize(int preSize);
		int getPostSize()const;
		void setPostSize(int postSize);
};
