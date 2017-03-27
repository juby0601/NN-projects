﻿#include "Runner.h"
#include "Config.h"
#include "DataIn.h"
#include "Input.h"
#include "HiddenLayer.h"
#include "Output.h"
#include "DataOut.h"
#include <cstddef>

using namespace std;

Runner::Runner()
{
	MLP.resize(NUMBER_OF_LAYERS);
}

void Runner::Training(){
	string nameOfTheFile = "StockPrice.txt";
	DataIn dataIn(nameOfTheFile);
	data = dataIn.GetData();
	Layer inputLayer;
	vector<double> stockPriceInput;
	for (unsigned int i = 0; i < WINDOW_SIZE; i++){
		stockPriceInput.push_back(data[2][i]);
	}
	MLP.at(0).InitInputlayer(WINDOW_SIZE, stockPriceInput);
	MLP.at(0).ComputeOutputs();
	for (unsigned int i = 1; i<MLP.size(); i++){
		if (i == NUMBER_OF_LAYERS-1){
			MLP.at(i).Init(1,MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}else{
			MLP.at(i).Init(HIDDEN_LAYER_NEURONS,MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}
	}

	double error = (MLP.at(3).GetOutput().at(0) - ((data[1][WINDOW_SIZE]-data[1][WINDOW_SIZE-1])/data[1][WINDOW_SIZE-1]));

	while ((0.5*error*error) > ERROR_THRESHOLD){
		Backpropogation(LERANING_RATE, MLP,error);
		for (unsigned int i = 1; i<MLP.size(); i++){
			MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}
		error = (MLP.at(3).GetOutput().at(0) - ((data[1][WINDOW_SIZE]-data[1][WINDOW_SIZE-1])/data[1][WINDOW_SIZE-1]));
		//cout << (0.5*error*error) << endl;
	}

	cout << "Finished training" << endl;
	cout << "Real value: " << data[1][WINDOW_SIZE] << endl;
	cout << "Predicted value: " << MLP.at(3).GetOutput().at(0)*data[1][WINDOW_SIZE-1]+data[1][WINDOW_SIZE-1] << endl;
	cout << "Difference: " << data[1][WINDOW_SIZE] - (MLP.at(3).GetOutput().at(0)*data[1][WINDOW_SIZE-1]+data[1][WINDOW_SIZE-1]) << endl;
	cout << endl;
}

void Runner::Backpropogation(double learningRate, vector<Layer> &MLP, double error){
	vector< vector<double> > weightTemps;
	vector<double> weightTemp;
	vector<double> inputTemp;

	for (unsigned int i = MLP.size()-1; i>0; i--){
		for (unsigned int j = 0; j<MLP[i].LayerSize(); j++){
			weightTemp = MLP[i].GetNeuron(j).getWeights();
			inputTemp = MLP[i].GetInput();

			if (i == (MLP.size()-1)){
				for (unsigned int k = 0; k<weightTemp.size(); k++){
					weightTemp[k] += learningRate*error*inputTemp[k];
				}
			}else{
				for (unsigned int k = 0; k<weightTemp.size(); k++){
					for (unsigned int t = 0; t<MLP[i+1].LayerSize(); t++){
						weightTemp[k] += learningRate*error*inputTemp[k]*MLP[i+1].GetNeuron(t).getWeights()[j];
					}
				}
			}

			weightTemps.push_back(weightTemp);
		}
	}

	int weightCounter = 0;
	for (unsigned int i = MLP.size()-1; i>0; i--){
		for (unsigned int j = 0; j<MLP[i].LayerSize(); j++){
			MLP[i].GetNeuron(j).setWeights(weightTemps[weightCounter]);
			weightCounter++;
		}
	}
}

void Runner::Prediction(int time){
	vector<double> initializer;
	vector<double> stockPriceInput;
	vector<double> predictedStockPriceChange;
	vector<double> predictedStockPrice;
	predictedStockPrice.push_back(data[1][WINDOW_SIZE-1]);
	for (unsigned int i = 0; i<time; i++){
		int counter = 0;
		for (unsigned int j = 0; j < WINDOW_SIZE; j++){
			if (j+i < WINDOW_SIZE){
				stockPriceInput.push_back(data[2][j+i]);
			}else if (i > WINDOW_SIZE){
				stockPriceInput.push_back(predictedStockPriceChange[counter+(i-WINDOW_SIZE)]);
				counter++;
			}else{
				stockPriceInput.push_back(predictedStockPriceChange[counter]);
				counter++;
			}
		}
		MLP.at(0).InitInputlayer(WINDOW_SIZE,stockPriceInput);
		MLP.at(0).ComputeOutputs();
		stockPriceInput = initializer;
		for (unsigned int k = 1; k<MLP.size(); k++){
			MLP.at(k).UpdateLayer(MLP.at(k-1).GetOutput());
			MLP.at(k).ComputeOutputs();
		}
		predictedStockPriceChange.push_back(MLP.at(3).GetOutput().at(0));
		predictedStockPrice.push_back(predictedStockPriceChange[i]*predictedStockPrice[i]+predictedStockPrice[i]);
	}

	cout << "Prediction" << endl;
	cout << "Real value: " << data[1][WINDOW_SIZE+time-1] << endl;
	cout << "Predicted value: " << predictedStockPrice[time] << endl;
	cout << "Difference: " << data[1][WINDOW_SIZE+time-1] - predictedStockPrice[time] << endl;
}

Runner::~Runner()
{
}