#pragma once
#include <vector>
#include <stdlib.h> 

class Neuron
{
public:
	Neuron();
	~Neuron();
	void Init(std::vector<double> &inputVector);
	void Init(double &input);
	double ComputeOutput();

private:
	void GenerateInitialWeights();

	std::vector<double> inputs;
	std::vector<double> weights;
	std::vector<double> product;
	double Sum(std::vector<double> &vector);
};
