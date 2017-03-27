#pragma once
#include <vector>

class Neuron
{
public:
	Neuron();
	~Neuron();
	void Init(int inputs);
	double FeedForward(std::vector<double> &inputs);

private:
	std::vector<double> weights;
	std::vector<double> product;
	double Sum(std::vector<double> &vector);
};
