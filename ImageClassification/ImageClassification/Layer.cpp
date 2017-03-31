#include "Layer.h"

using namespace std;

Layer::Layer() {
}

Layer::~Layer() {
}

void Layer::Init(unsigned int layerNeurons, vector<double> inputVector) {
	inputs = inputVector;
	neurons.resize(layerNeurons+1);
	outputs.resize(layerNeurons+1);
	for (unsigned int i = 0; i < neurons.size()-1; i++) {
		neurons.at(i).Init(inputs);
	}
	neurons.at(neurons.size()-1).Init(BIAS);
}

void Layer::InitInputlayer(unsigned int windowSize, vector<double> inputVector) {
	inputs = inputVector;
	neurons.resize(windowSize+1);
	outputs.resize(windowSize+1);
	for (unsigned int i = 0; i < neurons.size()-1; i++) {
		neurons.at(i).Init(inputs[i]);
	}
	neurons.at(neurons.size()-1).Init(BIAS);
}

void Layer::UpdateInputLayer(vector<double> inputVector){
	inputs = inputVector;
	for (unsigned int i = 0; i < neurons.size()-1; i++) {
		neurons.at(i).UpdateNeuron(inputs[i]);
	}
	neurons.at(neurons.size()-1).UpdateNeuron(BIAS);
}

void Layer::UpdateLayer(std::vector<double> inputVector){
	inputs = inputVector;
	for (unsigned int i = 0; i < neurons.size()-1; i++) {
		neurons.at(i).UpdateNeuron(inputs);
	}
	neurons.at(neurons.size()-1).UpdateNeuron(BIAS);
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
