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
	std::vector<double> GetInput();
	int LayerSize();
	Neuron &GetNeuron(unsigned int index);
	void UpdateLayer(std::vector<double> inputVector);
private:
	std::vector<double> outputs;
	std::vector<double> inputs;
	std::vector<Neuron> neurons;
};
