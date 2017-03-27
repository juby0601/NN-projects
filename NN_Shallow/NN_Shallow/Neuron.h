#pragma once
#include <vector>

class Neuron
{
public:
	Neuron();
	~Neuron();
	void Init(int inputChannels);
	void Input(double input, int index);
	void ComputeOutput();
	double GetOutput();

private:
	std::vector<double> inputs;
	std::vector<double> weights;
	std::vector<double> product;
	double Sum(std::vector<double> &vector);

	double output;
};
