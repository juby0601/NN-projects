#include "Config.h"
#include "Neuron.h"
#include <iostream>

using namespace std;

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

void Neuron::Init(double &input) {
	vector<double> inputTemp;
	inputTemp.push_back(input);
	inputs = inputTemp;
	weights.resize(1);
	product.resize(1);

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
		double r = ((double) rand() / (RAND_MAX));
		weights.at(i) = WEIGHT_SCALE * (r*2-1);
	}
}

double Neuron::Sum(std::vector<double> &vector) {
	double sum = 0;
	for (unsigned int i = 0; i < vector.size(); i++) {
		sum += vector.at(i);
	}
	return sum;
}
