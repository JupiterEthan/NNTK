#include "Par.h"
#include <string.h>

Par::Par()
{
	numLayers = 2;
	hiddenNum = 32;
	
	epoch = 20;
	
	eta = 0.1;
	alpha = 1.0;
	
	factor = 1.0;
	momentum = 0.0;
	
	trainList = new char[1];
	testList = new char[1];
	trainList[0] = '\0';
	testList[0] = '\0';
}

Par::Par(const Par& par)
{
	numLayers = par.getNumLayers();
	hiddenNum = par.getHiddenNum();
	featureDim = par.getFeatureDim();
	
	epoch = par.getEpoch();
	
	eta = par.getEta();
	alpha = par.getAlpha();
	
	factor = par.getFactor();
	momentum = par.getMomentum();
	
	trainList = new char[strlen(par.trainList)+1];
	testList = new char[strlen(par.testList)+1];
	
	memcpy(trainList,par.trainList,sizeof(char)*(strlen(par.trainList)+1));
	memcpy(testList,par.testList,sizeof(char)*(strlen(par.testList)+1));
}

void Par::operator=(const Par& par)
{
	delete[] trainList;
	delete[] testList;
	
	numLayers = par.getNumLayers();
	hiddenNum = par.getHiddenNum();
	featureDim = par.getFeatureDim();
	
	epoch = par.getEpoch();
	
	eta = par.getEta();
	alpha = par.getAlpha();
	
	factor = par.getFactor();
	momentum = par.getMomentum();
	
	trainList = new char[strlen(par.trainList)+1];
	testList = new char[strlen(par.testList)+1];
	
	memcpy(trainList,par.trainList,sizeof(char)*(strlen(par.trainList)+1));
	memcpy(testList,par.testList,sizeof(char)*(strlen(par.testList)+1));
}

Par::~Par()
{
	delete[] trainList;
	delete[] testList;
}

void Par::setTrainList(const char* list)
{
	delete[] trainList;
	
	trainList = new char[strlen(list)+1];
	memcpy(trainList,list,sizeof(char)*(strlen(list)+1));
}

void Par::setTestList(const char* list)
{
	delete[] testList;
	
	testList = new char[strlen(list)+1];
	memcpy(testList,list,sizeof(char)*(strlen(list)+1));
}

int Par::getNumLayers()const
{
	return numLayers;
}

void Par::setNumLayers(int numLayers)
{
	this->numLayers = numLayers;
	
	return;
}

int Par::getHiddenNum()const
{
	return hiddenNum;
}

void Par::setHiddenNum(int hiddenNum)
{
	this->hiddenNum = hiddenNum;
	
	return;
}

int Par::getFeatureDim()const
{
	return featureDim;
}

void Par::setFeatureDim(int featureDim)
{
	this->featureDim = featureDim;
	
	return;
}

int Par::getEpoch()const
{
	return epoch;
}

void Par::setEpoch(int epoch)
{
	this->epoch = epoch;
	
	return;
}

double Par::getEta()const
{
	return eta;
}

void Par::setEta(double eta)
{
	this->eta = eta;
	
	return;
}

double Par::getAlpha()const
{
	return alpha;
}

void Par::setAlpha(double alpha)
{
	this->alpha = alpha;
	
	return;
}

double Par::getFactor()const
{
	return factor;
}

void Par::setFactor(double factor)
{
	this->factor = factor;
	
	return;
}

double Par::getMomentum()const
{
	return momentum;
}

void Par::setMomentum(double momentum)
{
	this->momentum = momentum;
	
	return;
}



