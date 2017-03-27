#include "Layer.h"

using namespace std;

Layer::Layer() {
}

Layer::~Layer() {
}

void Layer::Init(unsigned int layerNeurons, std::vector<double> inputVector) {
	inputs = inputVector;
	neurons.resize(layerNeurons);
	outputs.resize(layerNeurons);
	for (unsigned int i = 0; i < neurons.size(); i++) {
		neurons.at(i).Init(inputs);
	}
}

void Layer::InitInputlayer(unsigned int windowSize, std::vector<double> inputVector) {
	inputs = inputVector;
	neurons.resize(windowSize);
	outputs.resize(windowSize);
	for (unsigned int i = 0; i < neurons.size(); i++) {
		neurons.at(i).Init(inputs[i]);
	}
}

void Layer::ComputeOutputs() {
	for (unsigned int i = 0; i < neurons.size(); i++) {
		outputs.at(i) =	neurons.at(i).ComputeOutput();
	}
}

vector<double> Layer::GetOutput() {
	return outputs;
}

Neuron & Layer::GetNeuron(unsigned int index) {
	return neurons.at(index);
}
