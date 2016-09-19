#pragma once
#include "Model.h"
#include "Label.h"
#include "Instance.h"
#include "Layer.h"
#include "Weights.h"
#include "Bias.h"
#include "Delta.h"
#include "Par.h"

void usage();

Par parseCmd(int argc,char** argv);

double sigmoid(double x,double alpha);

int getInstanceSize(const char* fileList);

void dataReader(const Par& par,const char* dataType,Label& label,Instance& instance);

void trainNormalize(Instance& instance,double* mean,double* variance);
void testNormalize(Instance& instance,const double* mean,const double* variance);

void trainNormalize(Instance& instance,double* mean,double* max,double* min);
void testNormalize(Instance& instance,const double* mean,const double* max,const double* min);

void initModel(Model& model,const Par& par);

void initLayer(Layer& layer,double alpha);

void initWeights(Weights& weights);

void initBias(Bias& bias);

double getOutput(Model& model,const double* feature);

int classification(Model& model,const double* feature);

void swap(int& a,int& b);
void randomArrayGenerator(int size,int* array);
double innerProduct(const double* a,const double* b,int dim);
double errorRate(Model& model,const Label& label,const Instance& instance);
double accuracy(Model& model,const Label& label,const Instance& instance);
void showStatus(double* status,Model& model,const Label& label,const Instance& instance);

void DNNtrainer(Model& model,const Par& par,const Label& trainLabel,const Instance& trainInstance);

void DNNtester(Model& model,const Par& par,Label& predictLabel,const Label& testLabel,const Instance& testInstance);
