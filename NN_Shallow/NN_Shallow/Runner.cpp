#include "Runner.h"
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
	deltaWeights.resize(getNumberOfWeights());
}

void Runner::Training(){
	double predictedValue;
	double error = 0;
	for (unsigned int f = 0; f < EPOCHS; f++){ 
		error = 0;
		for (unsigned int i = 0; i < TOTAL_WINDOW_SIZE-WINDOW_SIZE; i++){
			predictedValue = PredictAValue(i);
			error += 0.5*(data[2][WINDOW_SIZE+i]-predictedValue)*(data[2][WINDOW_SIZE+i]-predictedValue);
			Backpropogation(LERANING_RATE,data[2][WINDOW_SIZE+i]-predictedValue);
		}
		cout << error << endl;
	}

	cout << "Finished training" << endl;
	cout << endl;
}

double Runner::PredictAValue(int k){
	vector<double> stockPriceInput;
	for (unsigned int j = 0; j < WINDOW_SIZE; j++){
		stockPriceInput.push_back(data[2][j+k]);
	}
	MLP.at(0).UpdateInputLayer(stockPriceInput);
	MLP.at(0).ComputeOutputs();

	for (unsigned int i = 1; i<MLP.size(); i++){
		MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
		MLP.at(i).ComputeOutputs();
	}

	return (MLP.at(MLP.size() - 1).GetOutput().at(0));
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

void Runner::Backpropogation(double learningRate, double error){
	vector<double> weightTemp;
	double errorSum = 0;
	double errorSumTemp = 0;
	int deltaWeightCounter = 0;
	// Loop through layers
	for (int i = MLP.size()-1; i>=0; i--){
		// Loop through neurons in each layer
		for (unsigned int j = 0; j<MLP[i].LayerSize(); j++){
			weightTemp = MLP[i].GetNeuron(j).getWeights();
			if (i == (MLP.size()-1)){
				for (unsigned int k = 0; k<weightTemp.size(); k++){
					deltaWeights[deltaWeightCounter] = learningRate*MLP[i].GetInput()[k]*error+ALPHA*deltaWeights[deltaWeightCounter];
					weightTemp[k] += deltaWeights[deltaWeightCounter];
					errorSumTemp += weightTemp[k]*error;
					deltaWeightCounter++;
				}
			}else{
				for (unsigned int k = 0; k<weightTemp.size(); k++){
					deltaWeights[deltaWeightCounter] = learningRate*errorSum*MLP[i].GetInput()[k] + ALPHA*deltaWeights[deltaWeightCounter];
					weightTemp[k] += deltaWeights[deltaWeightCounter];
					errorSumTemp += weightTemp[k]*errorSum;
					deltaWeightCounter++;
				}
			}
			MLP[i].GetNeuron(j).setWeights(weightTemp);
		}
		errorSum = errorSumTemp;
		errorSumTemp = 0;
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

	cout << "Prediction" << endl;
	cout << "Real value: " << data[1][TOTAL_WINDOW_SIZE+i] << endl;
	cout << "Predicted value: " << predictedStockPrice[i+1] << endl;
	cout << "Difference: " << data[1][TOTAL_WINDOW_SIZE+i] - predictedStockPrice[i] << endl;
	cout << "Error in percentage: " << (data[1][TOTAL_WINDOW_SIZE+i] - predictedStockPrice[i+1])/data[1][TOTAL_WINDOW_SIZE+i]*100 << endl;
	cout << endl;

	}
	/*
	cout << "Prediction" << endl;
	cout << "Real value: " << data[1][TOTAL_WINDOW_SIZE+time-1] << endl;
	cout << "Predicted value: " << predictedStockPrice[time] << endl;
	cout << "Difference: " << data[1][TOTAL_WINDOW_SIZE+time-1] - predictedStockPrice[time] << endl;
	cout << "Error in percentage: " << (data[1][TOTAL_WINDOW_SIZE+time-1] - predictedStockPrice[time])/data[1][TOTAL_WINDOW_SIZE+time-1]*100 << endl;
	cout << endl;
	*/
}

int Runner::getNumberOfWeights(){
	int numberOfWeights = 0;
	for (int i = MLP.size()-1; i>=0; i--){
		for (unsigned int j = 0; j<MLP[i].LayerSize(); j++){
			for (unsigned int k = 0; k<MLP[i].GetNeuron(j).getWeights().size(); k++){
				cout << MLP[i].GetNeuron(j).getWeights()[k] << " ";
				numberOfWeights++;
			}
			cout << endl;
		}
	}
	cout << numberOfWeights << endl;
	return numberOfWeights;
}

double Runner::getDesiredOutput(int k){
	return data[2][WINDOW_SIZE+k];
}

Runner::~Runner(){}