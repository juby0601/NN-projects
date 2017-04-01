#pragma once
#include "Layer.h"
#include <arrayfire.h>
#include <vector>

class Runner
{
private:
	std::vector<Layer> MLP;
	af::array data;
	af::array testData;
	af::array deltaWeights;
	void Backpropogation(double learningRate, af::array &error, af::array &out);
	int GetNumberOfWeights();
	int FindIndexOfMax(af::array &input);
public:
	Runner();
	af::array PredictAValue(int classType, int imageNr);
	af::array PredictValues();
	void Training();
	double GetDesiredOutput(int k);
	~Runner();
};


