#pragma once

class Delta
{
	private:
		int size;
		
	public:
		double* del;
		
		Delta();
		Delta(const Delta& delta);
		
		~Delta();
		
		void operator=(const Delta& delta);
		
		int getSize()const;
		void setSize(int size);
};
