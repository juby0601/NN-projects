#pragma once
#include "Neuron.h"
#include <vector>

class Layer
{
public:
	Layer();
	~Layer();
	void Init(Layer* pPrevious, Layer* pNext);
	void FeedFoward();
	unsigned int GetNeurons();
	Neuron &GetNeuron(unsigned int index);
private:
	std::vector<Neuron> neurons;
	Layer* pPreviousLayer;
	Layer* pNextLayer;
};
