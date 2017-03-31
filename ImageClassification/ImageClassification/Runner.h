#pragma once
#include<vector>
#include "Layer.h"

class Runner
{
private:
	std::vector<Layer> MLP;
	std::vector<std::vector<std::vector<double>> > data;
	std::vector< vector<double> > testData;
	std::vector<double> deltaWeights;
	void Backpropogation(double learningRate, double error, double out);
	int GetNumberOfWeights();
	int FindIndexOfMax(vector<double> input);
public:
	Runner();
	vector<double> PredictAValue(int classType, int imageNr);
	std::vector<int> PredictValues();
	void Training();
	double GetDesiredOutput(int k);
	~Runner();
};


