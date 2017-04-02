#include "Layer.h"

using namespace std;

Layer::Layer() {
}

Layer::~Layer() {
}

void Layer::Init(unsigned int layerNeurons, af::array &inputVector) {
	inputs = inputVector;
	numberOfNeurons = layerNeurons;
	deltaWeights = af::constant(0,inputVector,dims(0), layerNeurons);
	weights = (WEIGHT_SCALE*af::randu(inputVector.dims(0), layerNeurons, f64)) - 1;
}

void Layer::InitInputlayer(unsigned int windowSize, af::array &inputVector) {
	af::array tempArray = af::constant(BIAS,1, f64);
	inputs = af::join(0, inputVector, tempArray);
	numberOfNeurons = windowSize + 1;
	deltaWeights = af::constant(0,1, inputVector.dims(0));
	weights = (WEIGHT_SCALE*af::randu(1, inputVector.dims(0), f64)) - 1;
}

void Layer::UpdateLayer(af::array inputVector) {
	inputs = inputVector;
}

void Layer::UpdateInputLayer(af::array inputVector){
	af::array tempArray = af::constant(BIAS, 1, f64);
	inputs = af::join(0, inputVector, tempArray);
}

void Layer::ComputeOutputs() {
	outputs = af::matmulTN(inputs, weights);
	ActivationFunction(outputs);
}

af::array& Layer::GetOutput() {
	return outputs;
}

af::array& Layer::GetInput() {
	return inputs;
}

int Layer::LayerSize(){
	return numberOfNeurons;
}

void Layer::ActivationFunction(af::array &input) {
	//sigmoid
	input = 1 / (1 + af::exp(-input));
}
