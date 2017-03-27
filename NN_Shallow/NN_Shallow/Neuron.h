#pragma once
#include <vector>
#include <stdlib.h> 

class Neuron
{
public:
	Neuron();
	~Neuron();
	void Init(std::vector<double> &inputVector);
	void Init(double input);
	double ComputeOutput();
	std::vector<double> getWeights();
	void setWeights(std::vector<double> &inputWeights);
	void UpdateNeuron(std::vector<double> inputVector);
	void UpdateNeuron(double input);
private:
	void GenerateInitialWeights();

	std::vector<double> inputs;
	std::vector<double> weights;
	std::vector<double> product;
	double Sum(std::vector<double> &vector);
};
