#pragma once
#include<vector>
#include "Layer.h"

class Runner
{
private:
	std::vector<Layer> MLP;
	std::vector<std::vector<double> > data;
	std::vector<double> deltaWeights;
	void Backpropogation(double learningRate, double error, double out);
	int getNumberOfWeights();
	void Normalization();
public:
	Runner();
	double PredictAValue(int k);
	std::vector<double> PredictValues(int start, int end);
	void Training();
	double getDesiredOutput(int k);
	~Runner();
};


