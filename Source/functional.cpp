#include "functional.h"
#include <cmath>
#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <ctype.h>
#include "Backprop.h"
#include <cfloat>
using namespace std;

void usage()
{
	cout<<endl
		<<"Usage: nntk -i trainList -o testList -f featureDim [-p epoch] [-n numLayers] [-h hiddenNum] "
		<<"[-e eta] [-a alpha] [-d factor] [-m momentum]"
		<<endl
		<<endl
		<<"Parameters description:"
		<<endl
		<<"[1]  -i - [primary parameter] specify the full path (including the file name) of the training set filelist."
		<<endl
		<<"[2]  -o - [primary parameter] specify the full path (including the file name) of the test set filelist."
		<<endl
		<<"[3]  -f - [primary parameter] specify the dimensionality of the input features."
		<<endl
		<<"[4]  -p - [optional parameter] specify the number of epoches used in the training stage. (default: 20)"
		<<endl
		<<"[5]  -n - [optional parameter] specify the number of layers (not including the input layer) in the neural network. (default: 2)"
		<<endl
		<<"[6]  -h - [optional parameter] specify the number of neurons in each hidden layer. (default: 32)"
		<<endl
		<<"[7]  -e - [optional parameter] specify the learning rate when updaing. (default: 0.1)"
		<<endl
		<<"[8]  -a - [optional parameter] specify the alpha value within the sigmoid function. (default: 1.0)"
		<<endl
		<<"[9]  -d - [optional parameter] set the learning rate self-adaptive and specify the factor. (default: 1.0)"
		<<endl
		<<"[10] -m - [optional parameter] set the momentum factor. (default: 0.0)"
		<<endl
		<<endl
		<<"Example:"
		<<endl
		<<"nntk -i E:/ml/trainlist.txt -o E:/ml/testlist.txt -f 38 -p 50 -n 4 -h 64 -e 0.01 -a 0.1 -d 0.8"
		<<endl;
			
	return;
}

Par parseCmd(int argc,char** argv)
{	
	Par par;

	if(argc < 7 || argc > 19 || argc%2 == 0)
	{
		usage();
		exit(0);
	}
	else
	{	
		if(strcmp(argv[1],"-i"))
		{
			usage();
			exit(0);
		}
		else
		{
			fstream file;
			file.open(argv[2],ios::in);
			
			if(!file)
			{
				cout<<"Error: invalid trainList path."<<endl;
				exit(0);
			}
			else
			{
				file.close();
			}
			
			par.setTrainList(argv[2]);
		}
		
		if(strcmp(argv[3],"-o"))
		{
			usage();
			exit(0);
		}
		else
		{
			fstream file;
			file.open(argv[4],ios::in);
			
			if(!file)
			{
				cout<<"Error: invalid testList path."<<endl;
				exit(0);
			}
			else
			{
				file.close();
			}
			
			par.setTestList(argv[4]);
		}
		
		if(strcmp(argv[5],"-f"))
		{
			usage();
			exit(0);
		}
		else
		{
			for(int i=0;i<strlen(argv[6]);i++)
			{
				if(!isdigit(argv[6][i]))
				{
					cout<<"Error: invalid featureDim input."<<endl;
					exit(0);
				}
			}
			
			par.setFeatureDim(atoi(argv[6]));
		}
		
		bool p = false;
		bool n = false;
		bool h = false;
		bool e = false;
		bool a = false;
		bool d = false;
		bool m = false;
		for(int j=7;j<argc;j+=2)
		{
			if(!strcmp(argv[j],"-p"))
			{
				if(p == true || n == true || h == true || e == true || a == true || d == true || m == true)
				{
					usage();
					exit(0);
				}
				
				p = true;
				
				for(int i=0;i<strlen(argv[j+1]);i++)
				{
					if(!isdigit(argv[j+1][i]))
					{
						cout<<"Error: invalid epoch input."<<endl;
						exit(0);
					}
				}
				
				par.setEpoch(atoi(argv[j+1]));
			}
			else if(!strcmp(argv[j],"-n"))
			{
				if(n == true || h == true || e == true || a == true || d == true || m == true)
				{
					usage();
					exit(0);
				}
				
				n = true;
				
				for(int i=0;i<strlen(argv[j+1]);i++)
				{
					if(!isdigit(argv[j+1][i]))
					{
						cout<<"Error: invalid featureDim input."<<endl;
						exit(0);
					}
				}
				
				par.setNumLayers(atoi(argv[j+1]));
			}
			else if(!strcmp(argv[j],"-h"))
			{
				if(h == true || e == true || a == true || d == true || m == true)
				{
					usage();
					exit(0);
				}
				
				h = true;
				
				for(int i=0;i<strlen(argv[j+1]);i++)
				{
					if(!isdigit(argv[j+1][i]))
					{
						cout<<"Error: invalid hiddenNum input."<<endl;
						exit(0);
					}
				}
				
				par.setHiddenNum(atoi(argv[j+1]));
			}
			else if(!strcmp(argv[j],"-e"))
			{
				if(e == true || a == true || d == true || m == true)
				{
					usage();
					exit(0);
				}
				
				e = true;
				
				bool flag = false;
				for(int i=0;i<strlen(argv[j+1]);i++)
				{
					if(!isdigit(argv[j+1][i]))
					{
						if(argv[j+1][i] == '.' && flag == false)
						{
							flag = true;
						}
						else
						{
							cout<<"Error: invalid eta input."<<endl;
							exit(0);
						}
					}
				}
				
				par.setEta(atof(argv[j+1]));
			}
			else if(!strcmp(argv[j],"-a"))
			{
				if(a == true || d == true || m == true)
				{
					usage();
					exit(0);
				}
				
				a = true;
				
				bool flag = false;
				for(int i=0;i<strlen(argv[j+1]);i++)
				{
					if(!isdigit(argv[j+1][i]))
					{
						if(argv[j+1][i] == '.' && flag == false)
						{
							flag = true;
						}
						else
						{
							cout<<"Error: invalid alpha input."<<endl;
							exit(0);
						}
					}
				}
				
				par.setAlpha(atof(argv[j+1]));
			}
			else if(!strcmp(argv[j],"-d"))
			{
				if(d == true || m == true)
				{
					usage();
					exit(0);
				}
				
				d = true;
				
				bool flag = false;
				for(int i=0;i<strlen(argv[j+1]);i++)
				{
					if(!isdigit(argv[j+1][i]))
					{
						if(argv[j+1][i] == '.' && flag == false)
						{
							flag = true;
						}
						else
						{
							cout<<"Error: invalid adaptive factor input."<<endl;
							exit(0);
						}
					}
				}
				
				par.setFactor(atof(argv[j+1]));
			}
			else if(!strcmp(argv[j],"-m"))
			{
				if(m == true)
				{
					usage();
					exit(0);
				}
				
				m = true;
				
				bool flag = false;
				for(int i=0;i<strlen(argv[j+1]);i++)
				{
					if(!isdigit(argv[j+1][i]))
					{
						if(argv[j+1][i] == '.' && flag == false)
						{
							flag = true;
						}
						else
						{
							cout<<"Error: invalid momentum factor input."<<endl;
							exit(0);
						}
					}
				}
				
				par.setMomentum(atof(argv[j+1]));
			}
			else
			{
				usage();
				exit(0);
			}
		}	
	}
	
	return par;
}

double sigmoid(double x,double alpha)
{
	return 1.0 / (1.0 + exp(-alpha*x));
}

int getInstanceSize(const char* fileList)
{
	fstream files;
	string fileName;
	fstream dataFile;
	
	int size(0);
	
	files.open(fileList,ios::in);
	
	while(getline(files,fileName))
	{
		dataFile.open(fileName.c_str(),ios::in);
		
		string temp;
		
		while(getline(dataFile,temp))
		{
			size++;
		}
		
		size--;
		
		dataFile.close();
	}
	
	files.close();
	
	return size;
}

void dataReader(const Par& par,const char* dataType,Label& label,Instance& instance)
{
	fstream files;
	string fileName;
	fstream dataFile;
	
	
	int dim = par.getFeatureDim();
	char* fileList;
	if(!strcmp(dataType,"train"))
	{
		fileList = new char[strlen(par.trainList)+1];
		memcpy(fileList,par.trainList,sizeof(char)*(strlen(par.trainList)+1));
	}
	else if(!strcmp(dataType,"test"))
	{
		fileList = new char[strlen(par.testList)+1];
		memcpy(fileList,par.testList,sizeof(char)*(strlen(par.testList)+1));
	}
	else
	{
		cout<<"Error: invalid input."<<endl;
		exit(0);
	}
	int size = getInstanceSize(fileList);
	int i = 0;
	
	label = Label(size);
	instance = Instance(size,dim);
	
	files.open(fileList,ios::in);
	
	while(getline(files,fileName))
	{
		dataFile.open(fileName.c_str(),ios::in);
		
		string temp;
		getline(dataFile,temp);
		
		while(true)
		{
			if(!(dataFile>>temp))
			{
				break;
			}
			
			if(!strcmp(temp.c_str(),"N"))
			{
				label.lb[i] = 1.0;
			}
			else
			{
				label.lb[i] = 0.0;
			}
			
			for(int j=0;j<dim;j++)
			{
				dataFile>>instance.ins[i*dim+j];
			}
			
			i++;
		}
		dataFile.close();
	}
	
	files.close();
	
	delete[] fileList;
	
	return;
}


void trainNormalize(Instance& instance,double* mean,double* variance)
{
	for(int j=0;j<instance.getDim();j++)
	{
		mean[j] = 0.0;
		variance[j] = 0.0;
		
		for(int i=0;i<instance.getSize();i++)
		{
			mean[j] += instance.ins[i*instance.getDim()+j];
		}
		
		mean[j] /= double(instance.getSize());
		
		for(int i=0;i<instance.getSize();i++)
		{
			variance[j] += pow(instance.ins[i*instance.getDim()+j]-mean[j],2);
		}
		
		variance[j] /= double(instance.getSize());
	}
	
	for(int j=0;j<instance.getDim();j++)
	{		
		for(int i=0;i<instance.getSize();i++)
		{
			instance.ins[i*instance.getDim()+j] = (instance.ins[i*instance.getDim()+j]-mean[j]) / variance[j];
		}
	}
	
	return;
}

void testNormalize(Instance& instance,const double* mean,const double* variance)
{
	for(int j=0;j<instance.getDim();j++)
	{		
		for(int i=0;i<instance.getSize();i++)
		{
			instance.ins[i*instance.getDim()+j] = (instance.ins[i*instance.getDim()+j]-mean[j]) / variance[j];
		}
	}
	
	return;
}


void initModel(Model& model,const Par& par)
{
	int inputDim = par.getFeatureDim();
	int outputDim = 1;
	int numLayers = par.getNumLayers();
	int layerSize = par.getHiddenNum();
	double alpha = par.getAlpha();
	model = Model(numLayers);
	
	for(int i=0;i<numLayers;i++)
	{
		if(i == numLayers-1)
		{
			model.layers[i] = Layer(outputDim);
			initLayer(model.layers[i],alpha);
		}
		else
		{
			model.layers[i] = Layer(layerSize);
			initLayer(model.layers[i],alpha);
		}
		
		if(i == 0)
		{
			model.weights[i] = Weights(inputDim,layerSize);
			initWeights(model.weights[i]);
		}
		else if(i == numLayers-1)
		{
			model.weights[i] = Weights(layerSize,outputDim);
			initWeights(model.weights[i]);
		}
		else
		{
			model.weights[i] = Weights(layerSize,layerSize);
			initWeights(model.weights[i]);
		}
		
		if(i < numLayers-1)
		{
			model.bias[i] = Bias(layerSize);
			initBias(model.bias[i]);
		}
		else
		{
			model.bias[i] = Bias(outputDim);
			initBias(model.bias[i]);
		}
	}
}

void initLayer(Layer& layer,double alpha)
{
	for(int i=0;i<layer.getSize();i++)
	{
		(layer.neurons[i]).setAlpha(alpha);
	}
	
	return;
}

void initWeights(Weights& weights)
{
	srand(unsigned(time(0)));
	
	for(int i=0;i<weights.getPreSize();i++)
	{
		for(int j=0;j<weights.getPostSize();j++)
		{
			weights.w[i*weights.getPostSize()+j] = (rand() / double(RAND_MAX) - 0.5) * 2.0;
		}
	}
	
	return;
}

void initBias(Bias& bias)
{
	srand(unsigned(time(0)));
	
	for(int i=0;i<bias.getSize();i++)
	{
		bias.b[i] = (rand() / double(RAND_MAX) - 0.5) * 2.0;
	}
	
	return;
}

double getOutput(Model& model,const double* feature)
{
	register double net;
	
	for(register int i=0;i<model.getNumLayers();i++)
	{
		for(register int j=0;j<(model.weights[i]).getPreSize();j++)
		{
			for(register int k=0;k<(model.weights[i]).getPostSize();k++)
			{
				if(i == 0)
				{						
					net = 0.0;
					for(register int m=0;m<(model.weights[i]).getPreSize();m++)
					{
						net += feature[m] * (model.weights[i]).w[m*(model.weights[i]).getPostSize()+k];
					}
					net += (model.bias[i]).b[k];

					((model.layers[i]).neurons[k]).setInput(net);
					((model.layers[i]).neurons[k]).activate();
				}
				else
				{						
					net = 0.0;
					for(int m=0;m<(model.weights[i]).getPreSize();m++)
					{
						net += ((model.layers[i-1]).neurons[m]).getOutput() * (model.weights[i]).w[m*(model.weights[i]).getPostSize()+k];
					}
					net += (model.bias[i]).b[k];
					
					((model.layers[i]).neurons[k]).setInput(net);
					((model.layers[i]).neurons[k]).activate();
				}
			}
		}
	}
	
	return ((model.layers[model.getNumLayers()-1]).neurons[0]).getOutput();
}

int classification(Model& model,const double* feature)
{	
	double output = getOutput(model,feature);
	
	if(output >= 0.5)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void swap(int& a,int& b)
{
	int temp = a;
	a = b;
	b = temp;
	
	return;
}

void randomArrayGenerator(int size,int* array)
{
	for(int i=0;i<size;i++)
	{
		array[i] = i;
	}
	
	srand(unsigned(time(0)));
	
	int temp1;
	int temp2;
	
	for(int i=0;i<2*size;i++)
	{
		temp1 = rand() % size;
		temp2 = rand() % size;
		swap(array[temp1],array[temp2]);
	}
	
	return;
}

double innerProduct(const double* a,const double* b,int dim)
{
	double result = 0.0;
	
	for(int i=0;i<dim;i++)
	{
		result += a[i] * b[i];
	}
	
	return result;
}

double squareError(Model& model,const Label& label,const Instance& instance)
{
	double error = 0.0;
	
	for(int i=0;i<label.getSize();i++)
	{			
		error += pow(getOutput(model,instance.ins+i*instance.getDim())-label.lb[i],2);
	}
	
	error /= double(label.getSize());
	
	return error;
}

double accuracy(Model& model,const Label& label,const Instance& instance)
{
	int correct = 0;
	int temp;
	
	for(int i=0;i<label.getSize();i++)
	{
		temp = classification(model,instance.ins+i*instance.getDim());
		
		if(temp == int(label.lb[i]))
		{
			correct++;
		}
	}
	
	return double(correct) / double(label.getSize());
}

void showStatus(double* status,Model& model,const Label& label,const Instance& instance)
{
	double error = 0.0;
	int correct = 0;
	int temp;
	double output;
	
	for(int i=0;i<label.getSize();i++)
	{			
		output = getOutput(model,instance.ins+i*instance.getDim());
		error += pow(output-label.lb[i],2);
		
		if(output >= 0.5)
		{
			temp = 1;
		}
		else
		{
			temp = 0;
		}
		
		if(temp == int(label.lb[i]))
		{
			correct++;
		}
	}
	
	error /= double(label.getSize());
	
	status[0] = error;
	status[1] = double(correct) / double(label.getSize());
	
	return;
}

void DNNtrainer(Model& model,const Par& par,const Label& trainLabel,const Instance& trainInstance)
{
	double alpha = par.getAlpha();
	double eta = par.getEta();
	double factor = par.getFactor();
	double momentum = par.getMomentum();
	int epoch = par.getEpoch();
	int* array = new int[trainInstance.getSize()];
	Weights* newWeights = new Weights[model.getNumLayers()];
	Weights* oldDeltaWeights = new Weights[model.getNumLayers()];
	Bias* newBias = new Bias[model.getNumLayers()];
	Bias* oldDeltaBias = new Bias[model.getNumLayers()];
	
	double old_error;
	double error;
	double* status = new double[2];
	
	for(register int i=0;i<model.getNumLayers();i++)
	{
		newWeights[i] = model.weights[i];
		newBias[i] = model.bias[i];
		oldDeltaWeights[i] = model.weights[i];
		oldDeltaBias[i] = model.bias[i];
	}
	
	for(int e=0;e<epoch;e++)
	{
		if(e == 0)
		{
			cout<<squareError(model,trainLabel,trainInstance)<<"    "<<accuracy(model,trainLabel,trainInstance)<<endl;
		}
		randomArrayGenerator(trainInstance.getSize(),array);
		
		for(register int in=0;in<trainInstance.getSize();in++)
		{						
//			DWORD startTime = GetTickCount();
			
			getOutput(model,trainInstance.ins+array[in]*trainInstance.getDim());
			
//			cout<<"Run Time: "<<GetTickCount()-startTime<<endl;
			
			Backprop backprop(model,trainLabel.lb[array[in]],alpha);
			
			for(register int i=model.getNumLayers()-1;i>=0;i--)
			{
				for(register int j=0;j<(model.weights[i]).getPreSize();j++)
				{
					for(register int k=0;k<(model.weights[i]).getPostSize();k++)
					{
						if(i>0)
						{
							if(in == 0)
							{
								register double delta_w = eta*(backprop.delta[i]).del[k]*((model.layers[i-1]).neurons[j]).getOutput();
								oldDeltaWeights[i].w[j*(model.weights[i]).getPostSize()+k] = delta_w;
							
								register double delta_b = eta*(backprop.delta[i]).del[k];
								oldDeltaBias[i].b[k] = delta_b;
								
								newWeights[i].w[j*(model.weights[i]).getPostSize()+k] = 
								(model.weights[i]).w[j*(model.weights[i]).getPostSize()+k] + delta_w;
								
								newBias[i].b[k] = (model.bias[i]).b[k] + delta_b;
							}
							else
							{
								register double delta_w = eta*(backprop.delta[i]).del[k]*((model.layers[i-1]).neurons[j]).getOutput() +
									momentum*oldDeltaWeights[i].w[j*(model.weights[i]).getPostSize()+k];
								oldDeltaWeights[i].w[j*(model.weights[i]).getPostSize()+k] = delta_w;
							
								register double delta_b = eta*(backprop.delta[i]).del[k] +
									momentum*oldDeltaBias[i].b[k];
								oldDeltaBias[i].b[k] = delta_b;
								
								newWeights[i].w[j*(model.weights[i]).getPostSize()+k] = 
								(model.weights[i]).w[j*(model.weights[i]).getPostSize()+k] + delta_w;
								
								newBias[i].b[k] = (model.bias[i]).b[k] + delta_b;
							}
						}
						else
						{
							if(in == 0)
							{
								register double delta_w = eta*(backprop.delta[i]).del[k]*trainInstance.ins[array[in]*trainInstance.getDim()+j];
								oldDeltaWeights[i].w[j*(model.weights[i]).getPostSize()+k] = delta_w;
								
								register double delta_b = eta*(backprop.delta[i]).del[k];
								oldDeltaBias[i].b[k] = delta_b;
								
								newWeights[i].w[j*(model.weights[i]).getPostSize()+k] = 
								(model.weights[i]).w[j*(model.weights[i]).getPostSize()+k] + delta_w;
								
								newBias[i].b[k] = (model.bias[i]).b[k] + delta_b;
							}
							else
							{
								register double delta_w = eta*(backprop.delta[i]).del[k]*trainInstance.ins[array[in]*trainInstance.getDim()+j] +
									momentum*oldDeltaWeights[i].w[j*(model.weights[i]).getPostSize()+k];
								oldDeltaWeights[i].w[j*(model.weights[i]).getPostSize()+k] = delta_w;
								
								register double delta_b = eta*(backprop.delta[i]).del[k] +
									momentum*oldDeltaBias[i].b[k];
								oldDeltaBias[i].b[k] = delta_b;
								
								newWeights[i].w[j*(model.weights[i]).getPostSize()+k] = 
								(model.weights[i]).w[j*(model.weights[i]).getPostSize()+k] + delta_w;
								
								newBias[i].b[k] = (model.bias[i]).b[k] + delta_b;
							}	
						}
					}
				}
			}
			
			for(register int i=0;i<model.getNumLayers();i++)
			{
				model.weights[i] = newWeights[i];
				model.bias[i] = newBias[i];
			}
			
		}

		showStatus(status,model,trainLabel,trainInstance);
		
		if(e == 0)
		{
			error = status[0];
			old_error = error;
		}
		else
		{
			old_error = error;
			error = status[0];
		}
		
		if(error > old_error)
		{
			eta *= factor;
		}
		
		cout<<"epoch "<<e<<"    "<<error<<"    "<<status[1]<<"    "<<eta<<endl;
	}
	
	delete[] array;
	delete[] newWeights;
	delete[] newBias;
	delete[] oldDeltaWeights;
	delete[] oldDeltaBias;
	
	delete[] status;
	
	return;
}

void DNNtester(Model& model,const Par& par,Label& predictLabel,const Label& testLabel,const Instance& testInstance)
{
	predictLabel = Label(testLabel.getSize());
	
	int correct = 0;
	double accuracyRate;
	
	for(int i=0;i<testLabel.getSize();i++)
	{
		predictLabel.lb[i] = classification(model,testInstance.ins+i*testInstance.getDim());
		
		if(int(predictLabel.lb[i]) == int(testLabel.lb[i]))
		{
			correct++;
		}
	}
	
	accuracyRate = double(correct) / double(testLabel.getSize());
	
	cout<<"classification accuracy: "<<accuracyRate<<endl;
}
