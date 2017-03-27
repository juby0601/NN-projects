#pragma once
#include "Neuron.h"
#include <vector>
#include <cstddef>

class Layer
{
public:
	Layer();
	~Layer();
	void Init(unsigned int layerNeurons, std::vector<double> inputVector);
	void InitInputlayer(unsigned int windowSize, std::vector<double> inputVector); 
	void ComputeOutputs();
	std::vector<double> GetOutput();
	Neuron &GetNeuron(unsigned int index);
private:
	std::vector<double> outputs;
	std::vector<double> inputs;
	std::vector<Neuron> neurons;
};
