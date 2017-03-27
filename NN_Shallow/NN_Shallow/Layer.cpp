#include "Layer.h"

Layer::Layer() {
}

Layer::~Layer() {
}

void Layer::Init(unsigned int &layerNeurons, std::vector<double> &inputVector) {
	neuronQuantity = layerNeurons;
	inputs = inputVector;

	for (unsigned int i = 0; i < neurons.size(); i++) {
		neurons.at(i).Init(inputs);
	}
}

void Layer::ComputeOutputs() {
	for (unsigned int i = 0; i < neurons.size(); i++) {
		outputs.at(i) =	neurons.at(i).ComputeOutput();
	}
}

unsigned int Layer::GetNeurons() {
	return neurons.size();
}

Neuron & Layer::GetNeuron(unsigned int index) {
	return neurons.at(index);
}

