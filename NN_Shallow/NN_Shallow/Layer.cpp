#include "Layer.h"

using namespace std;

Layer::Layer() {
}

Layer::~Layer() {
}

void Layer::Init(unsigned int layerNeurons, vector<double> inputVector) {
	inputs = inputVector;
	neurons.resize(layerNeurons);
	outputs.resize(layerNeurons);
	for (unsigned int i = 0; i < neurons.size(); i++) {
		neurons.at(i).Init(inputs);
	}
}

void Layer::InitInputlayer(unsigned int windowSize, vector<double> inputVector) {
	inputs = inputVector;
	neurons.resize(windowSize);
	outputs.resize(windowSize);
	for (unsigned int i = 0; i < neurons.size(); i++) {
		neurons.at(i).Init(inputs[i]);
	}
}

void Layer::UpdateInputLayer(vector<double> inputVector){
	inputs = inputVector;
	for (unsigned int i = 0; i < neurons.size(); i++) {
		neurons.at(i).UpdateNeuron(inputs[i]);
	}
}

void Layer::UpdateLayer(std::vector<double> inputVector){
	inputs = inputVector;
	for (unsigned int i = 0; i < neurons.size(); i++) {
		neurons.at(i).UpdateNeuron(inputs);
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

vector<double> Layer::GetInput() {
	return inputs;
}

Neuron & Layer::GetNeuron(unsigned int index) {
	return neurons.at(index);
}

int Layer::LayerSize(){
	return neurons.size();
}
