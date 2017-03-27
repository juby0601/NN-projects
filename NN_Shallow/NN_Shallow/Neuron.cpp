#include "Neuron.h"

Neuron::Neuron() {
}

Neuron::~Neuron() {
}

void Neuron::Init(int inputChannels) {
	inputs.resize(inputChannels);
	weights.resize(inputChannels);
	product.resize(inputChannels);
}

void Neuron::Input(double input, int index) {
	inputs.at(index) = input;
}

void Neuron::ComputeOutput() {
	for (unsigned int i = 0; i < product.size(); i++) {
		product.at(i) = weights.at(i) * inputs.at(i);
	}
	output = Sum(product);
}

double Neuron::GetOutput() {
	return output;
}

double Neuron::Sum(std::vector<double> &vector) {
	double sum = 0;
	for (unsigned int i = 0; i < vector.size(); i++) {
		sum += vector.at(i);
	}
	return sum;
}
