#pragma once
#include<vector>
#include "Layer.h"

class Runner
{
private:
	std::vector<Layer> MLP;
	std::vector<std::vector<double> > data;
	std::vector<double> deltaWeights;
	std::vector<double> PredictValues();
	void Backpropogation(double learningRate, double error);
	int getNumberOfWeights();
public:
	Runner();
	double PredictAValue(int k);
	void Training();
	void Prediction(int time);
	double getDesiredOutput(int k);
	~Runner();
};


