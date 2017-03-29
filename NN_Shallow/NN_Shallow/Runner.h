#pragma once
#include<vector>
#include "Layer.h"

class Runner
{
private:
	std::vector<Layer> MLP;
	std::vector<std::vector<double> > data;
	std::vector<double> GetRegressionFunction();
	void Backpropogation(double learningRate, std::vector<double> error);
	double SumVector(std::vector<double> &vector);
public:
	Runner();
	void Training();
	void Prediction(int time);
	void printWeights();
	~Runner();
};


