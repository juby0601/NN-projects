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
	string nameOfTheFile = "StockPrice.txt";
	DataIn dataIn(nameOfTheFile);
	data = dataIn.GetData();
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
}

void Runner::Training(){
	vector<double> predictedValues = PredictValues();
	vector<double> errorVector;
	vector<double> rmsError;

	double error = 0;
	double previousError = 5000;
	for (unsigned int i = 0; i < predictedValues.size(); i++){
		errorVector.push_back(data[2][WINDOW_SIZE+i]-predictedValues[i]);
		rmsError.push_back(0.5*(data[2][WINDOW_SIZE+i]-predictedValues[i])*(data[2][WINDOW_SIZE+i]-predictedValues[i]));
		error = SumVector(rmsError);
	}

	cout << error << endl;
	while (error > ERROR_THRESHOLD){ 
		Backpropogation(LERANING_RATE,errorVector);
		errorVector.clear();
		rmsError.clear();
		predictedValues = PredictValues();
		for (unsigned int i = 0; i < predictedValues.size(); i++){
			errorVector.push_back(data[2][WINDOW_SIZE+i]-predictedValues[i]);
			rmsError.push_back(0.5*(data[2][WINDOW_SIZE+i]-predictedValues[i])*(data[2][WINDOW_SIZE+i]-predictedValues[i]));
			previousError = error;
			error = SumVector(rmsError);
		}
		cout << error << endl;
	}

	cout << "Finished training" << endl;
	cout << endl;
}

vector<double> Runner::PredictValues() {
	vector<double> stockPriceInput;
	vector<double> initializer;
	vector<double> predictedValues;

	for (unsigned int k = 0; k<TOTAL_WINDOW_SIZE-WINDOW_SIZE; k++){

		stockPriceInput = initializer;
		for (unsigned int j = 0; j < WINDOW_SIZE; j++){
			stockPriceInput.push_back(data[2][j+k]);
		}
								
		MLP.at(0).UpdateInputLayer(stockPriceInput);
		MLP.at(0).ComputeOutputs();

		for (unsigned int i = 1; i<MLP.size(); i++){
			MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}
		predictedValues.push_back(MLP.at(MLP.size() - 1).GetOutput().at(0));
	}
	return predictedValues;
}

void Runner::Backpropogation(double learningRate, vector<double> error){
	vector< vector<double> > weightTemps;
	vector<double> weightTemp;
	vector<double> inputTemp;

	// Loop through layers
	for (unsigned int i = MLP.size()-1; i>0; i--){

		// Loop through neurons in each layer
		for (unsigned int j = 0; j<MLP[i].LayerSize(); j++){
			
			weightTemp = MLP[i].GetNeuron(j).getWeights();
			inputTemp = MLP[i].GetInput();
			
			if (i == (MLP.size()-1)){
				MLP[i].GetNeuron(j).SetWeightProduct(1);
				for (unsigned int k = 0; k<weightTemp.size(); k++){
					weightTemp[k] += learningRate*inputTemp[k]*SumVector(error);
				}
			}else{
				MLP[i].GetNeuron(j).SetWeightProduct(0);

				// Loop through each connection going out of each neuron
				for (unsigned int t = 0; t<MLP[i + 1].LayerSize() - 1; t++) {

					// TODO: change eroor to be value instead of vector
					//weightTemp[k] += learningRate*SumVector(error)*inputTemp[k] * MLP[i + 1].GetNeuron(t).getWeights()[j];
					MLP[i].GetNeuron(j).SetWeightProduct(MLP[i].GetNeuron(j).GetWeightProduct() + MLP[i + 1].GetNeuron(t).getWeights()[j] * MLP[i + 1].GetNeuron(t).GetWeightProduct());
				}

				// Loop through weights going into each neuron
				for (unsigned int k = 0; k<weightTemp.size(); k++){
					weightTemp[k] += learningRate*SumVector(error)*inputTemp[k] * MLP[i].GetNeuron(j).GetWeightProduct();
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
	predictedStockPrice.push_back(data[1][TOTAL_WINDOW_SIZE-1]);
	for (unsigned int i = 0; i<time; i++){
		int counter = 0;
		for (unsigned int j = 0; j < TOTAL_WINDOW_SIZE; j++){
			if (j+i < TOTAL_WINDOW_SIZE){
				stockPriceInput.push_back(data[2][j+i]);
			}else if (i > TOTAL_WINDOW_SIZE){
				stockPriceInput.push_back(predictedStockPriceChange[counter+(i-TOTAL_WINDOW_SIZE)]);
				counter++;
			}else{
				stockPriceInput.push_back(predictedStockPriceChange[counter]);
				counter++;
			}
		}
		MLP.at(0).UpdateInputLayer(stockPriceInput);
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
	cout << "Real value: " << data[1][TOTAL_WINDOW_SIZE+time-1] << endl;
	cout << "Predicted value: " << predictedStockPrice[time] << endl;
	cout << "Difference: " << data[1][TOTAL_WINDOW_SIZE+time-1] - predictedStockPrice[time] << endl;
	cout << "Error in percentage: " << (data[1][TOTAL_WINDOW_SIZE+time-1] - predictedStockPrice[time])/data[1][TOTAL_WINDOW_SIZE+time-1]*100 << endl;
	cout << endl;
}

void Runner::printWeights(){
	int numberOfWeights = 0;
	for (unsigned int i = MLP.size()-1; i>0; i--){
		for (unsigned int j = 0; j<MLP[i].LayerSize(); j++){
			for (unsigned int k = 0; k<MLP[i].GetNeuron(j).getWeights().size(); k++){
				cout << MLP[i].GetNeuron(j).getWeights()[k] << " ";
				numberOfWeights++;
			}
			cout << endl;
		}
	}
	cout << numberOfWeights << endl;
}

double Runner::SumVector(std::vector<double> &vector) {
	double sum = 0;
	for (unsigned int i = 0; i < vector.size(); i++) {
		sum += vector.at(i);
	}
	return sum;
}

Runner::~Runner(){}