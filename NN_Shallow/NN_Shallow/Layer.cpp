#include "Layer.h"

Layer::Layer() {
}

Layer::~Layer() {
}

void Layer::Init(Layer* pPrevious, Layer* pNext) {
	pPreviousLayer = pPrevious;
	pNextLayer = pNext;
}

void Layer::FeedFoward() {
	for (unsigned int i = 0; i < neurons.size(); i++) {
		neurons.at(i).ComputeOutput();
		if (pNextLayer != NULL) {
			for (unsigned int j = 0; j < pNextLayer->GetNeurons(); j++) {
				pNextLayer->GetNeuron(j).Input(neurons.at(i).GetOutput(), i);
			}
		}
	}
}

unsigned int Layer::GetNeurons() {
	return neurons.size();
}

Neuron & Layer::GetNeuron(unsigned int index) {
	return neurons.at(index);
}

