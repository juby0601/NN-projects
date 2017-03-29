#pragma once
#include<vector>
#include "Layer.h"

class Runner
{
private:
	std::vector<Layer> MLP;
	std::vector<std::vector<double> > data;
public:
	Runner();
	void Training();
	void Backpropogation(double learningRate, std::vector<Layer> &MLP, double error);
	void Prediction(int time);
	void printWeights();
	~Runner();
};


