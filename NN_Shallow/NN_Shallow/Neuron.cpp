#include "Neuron.h"

Neuron::Neuron() {
}

Neuron::~Neuron() {
}

void Neuron::Init(int inputs) {
	weights.resize(inputs);
	product.resize(inputs);
}

double Neuron::FeedForward(std::vector<double> &inputs) {
	for (unsigned int i = 0; i < product.size(); i++) {
		product.at(i) = weights.at(i) * inputs.at(i);
	}

	return Sum(product);
}

double Neuron::Sum(std::vector<double> &vector) {
	double sum = 0;

	for (unsigned int i = 0; i < vector.size(); i++) {
		sum += vector.at(i);
	}
	
	return sum;
}
