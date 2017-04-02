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
	void Backpropogation(af::array &error, af::array &out);
public:
	Runner();
	void Training();
	af::array PredictAValue(int classType, int imageNr);
	af::array PredictValues();
	af::array GetDesiredOutput(int k);
	~Runner();
};


