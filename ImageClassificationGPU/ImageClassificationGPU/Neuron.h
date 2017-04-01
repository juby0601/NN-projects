#pragma once
#include <vector>
#include <stdlib.h>
#include <arrayfire.h>


class Neuron
{
public:
	Neuron();
	~Neuron();
	void Init(af::array &inputVector);
	void Neuron::Init(af::array input);
	af::array ComputeOutput();
	af::array getWeights();
	void setWeights(std::vector<double> &inputWeights);
	void UpdateNeuron(af::array inputVector);
	void UpdateNeuron(double input);
private:
	af::array Summation(af::array input);

	af::array inputs;
	af::array weights;
	af::array product;
	double ActivationFunction(double input);
	double weightProduct;
};
