#pragma once

class Label
{
	private:
		int size;
		
	public:
		double* lb;
		
		Label();
		Label(int size);
		Label(const Label& label);
		
		~Label();
		
		void operator=(const Label& label);
		
		int getSize()const;
};
