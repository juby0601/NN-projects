#pragma once
#include <vector>

class Neuron
{
public:
	Neuron();
	~Neuron();
	void Init(std::vector<double> &inputVector);
	double ComputeOutput();

private:
	void GenerateInitialWeights();

	std::vector<double> inputs;
	std::vector<double> weights;
	std::vector<double> product;
	double Sum(std::vector<double> &vector);
};
