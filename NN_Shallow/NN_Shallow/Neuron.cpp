#include "Config.h"
#include "Neuron.h"

Neuron::Neuron() {
}

Neuron::~Neuron() {
}

void Neuron::Init(std::vector<double> &inputVector) {
	inputs = inputVector;
	weights.resize(inputVector.size());
	product.resize(inputVector.size());

	GenerateInitialWeights();
}

double Neuron::ComputeOutput() {
	for (unsigned int i = 0; i < product.size(); i++) {
		product.at(i) = weights.at(i) * inputs.at(i);
	}
	return Sum(product);
}

void Neuron::GenerateInitialWeights() {
	for (unsigned int i = 0; i < weights.size(); i++) {
		weights.at(i) = WEIGHT_MIN + (std::rand() % (WEIGHT_MAX - WEIGHT_MIN + 1));
	}
}

double Neuron::Sum(std::vector<double> &vector) {
	double sum = 0;
	for (unsigned int i = 0; i < vector.size(); i++) {
		sum += vector.at(i);
	}
	return sum;
}
