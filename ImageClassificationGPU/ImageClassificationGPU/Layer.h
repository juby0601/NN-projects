#pragma once
#include "Config.h"
#include <vector>
#include <cstddef>
#include <arrayfire.h>

class Layer
{
public:
	Layer();
	~Layer();
	void Init(unsigned int layerNeurons, af::array &inputVector);
	void InitInputlayer(unsigned int windowSize, af::array &inputVector);
	void ComputeOutputs();
	af::array& GetOutput();
	af::array& GetInput();
	af::array& GetWeights() { return weights; };
	af::array& GetDeltaWeights() {return deltaWeights;};
	int LayerSize();
	void UpdateLayer(af::array inputVector);
	void UpdateInputLayer(af::array inputVector);
	void ActivationFunction(af::array &input);
	void ComputeOutputsInputLayer();
private:
	af::array outputs;
	af::array inputs;
	af::array weights;
	af::array deltaWeights;
	unsigned int numberOfNeurons;
};
