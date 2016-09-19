#include <iostream>
#include "Label.h"
#include "Instance.h"
#include "Model.h"
#include "functional.h"
#include "Par.h"
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
	Par par;
	Label trainLabel;
	Label testLabel;
	Label predictLabel;
	Instance trainInstance;
	Instance testInstance;
	Model model;
	
	double* mean;
	double* variance;
	double* max;
	double* min;
	
	par = parseCmd(argc,argv);
	
	cout<<"Reading training set..."<<endl;
	dataReader(par,"train",trainLabel,trainInstance);
	
	cout<<"Reading test set..."<<endl;
	dataReader(par,"test",testLabel,testInstance);	
	
	
	mean = new double[trainInstance.getDim()];
	variance = new double[trainInstance.getDim()];

	cout<<"Normalizing training set..."<<endl;
	trainNormalize(trainInstance,mean,variance);
	cout<<"Normalizing test set..."<<endl;
	testNormalize(testInstance,mean,variance);
	delete[] mean;
	delete[] variance;
	
	cout<<"Initializing model..."<<endl;
	initModel(model,par);

	cout<<"Training model..."<<endl;
	DNNtrainer(model,par,trainLabel,trainInstance);
	
	cout<<"Testing model..."<<endl;
	DNNtester(model,par,predictLabel,testLabel,testInstance);
	
	return 0;
}
