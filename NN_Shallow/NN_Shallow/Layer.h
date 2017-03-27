#pragma once
#include "Neuron.h"
#include <vector>
#include <cstddef>

class Layer
{
public:
	Layer();
	~Layer();
	void Init(unsigned int &layerNeurons, std::vector<double> &inputVector);
	void ComputeOutputs();
	unsigned int GetNeurons();
	Neuron &GetNeuron(unsigned int index);
private:
	std::vector<double> inputs;
	std::vector<double> outputs;
	std::vector<Neuron> neurons;
};
