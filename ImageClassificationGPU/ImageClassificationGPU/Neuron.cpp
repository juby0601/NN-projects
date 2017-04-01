#include "Config.h"
#include "Neuron.h"
#include <af/util.h>
#include <math.h>
#include <iostream>

using namespace std;

Neuron::Neuron() {
}

Neuron::~Neuron() {
}

void Neuron::Init(af::array &inputVector) {
	inputs = inputVector;
	weights = (WEIGHT_SCALE*af::randu(inputVector.dims(0), f64)) - 1;
	weights = af::array(inputVector.dims(0), f64);
	product = af::array(inputVector.dims(0), f64);
}

void Neuron::Init(af::array input) {
	inputs = input;
	weights = (WEIGHT_SCALE*af::randu(1, f64)) - 1;
	product = af::array(1, f64);
}

void Neuron::UpdateNeuron(af::array inputVector){
	inputs = inputVector;
}

void Neuron::UpdateNeuron(double input){
	inputs = af::array(1, f32);
	inputs(0) = input;
}

af::array Neuron::ComputeOutput() {
	for (int i = 0; i < product.dims(0); i++) {
		product(i) = weights(i) * inputs(i);
	}
	return Summation(product);
}

af::array Summation(af::array input) {
	af::array output(1, f64);
	for (int i = 0; i < input.dims(0); i++) {
		output(0) += input(i);
	}
	return output;
}

af::array Neuron::getWeights(){
	return weights;
}

void Neuron::setWeights(vector<double> &inputWeights){
	for (int i = 1; i<inputWeights.size(); i++){
		weights[i] = inputWeights[i];
	}
}