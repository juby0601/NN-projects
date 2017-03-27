#pragma once
#include<vector>
#include "Layer.h"

class Runner
{
public:
	Runner();
	void Training();
	void Backpropogation(double learningRate, std::vector<Layer> &MLP, double error);
	~Runner();
};


