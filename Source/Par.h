#pragma once

class Par
{
	private:
		int numLayers;
		int hiddenNum;
		int featureDim;
		
		int epoch;
		
		double eta;
		double alpha;
		
		double factor; // adaptive factor
		double momentum;
		
	public:
		char* trainList;
		char* testList;
		
		Par();
		
		Par(const Par& par);
		
		void operator=(const Par& par);
		
		~Par();
		
		void setTrainList(const char* list);
		void setTestList(const char* list);
		
		int getNumLayers()const;
		void setNumLayers(int numLayers);
		
		int getHiddenNum()const;
		void setHiddenNum(int hiddenNum);
		
		int getFeatureDim()const;
		void setFeatureDim(int featureDim);
		
		int getEpoch()const;
		void setEpoch(int epoch);
		
		double getEta()const;
		void setEta(double eta);
		
		double getAlpha()const;
		void setAlpha(double alpha);
		
		double getFactor()const;
		void setFactor(double factor);
		
		double getMomentum()const;
		void setMomentum(double momentum);
};
