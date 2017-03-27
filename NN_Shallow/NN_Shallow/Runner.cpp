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
{}

void Runner::Training(){
	string nameOfTheFile = "StockPrice.txt";
	DataIn dataIn(nameOfTheFile);
	vector<vector<double> > data = dataIn.GetData();
	vector<Layer> MLP(NUMBER_OF_LAYERS);
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
	cout << (0.5*error*error) << endl;

	while ((0.5*error*error) > ERROR_THRESHOLD){
		Backpropogation(LERANING_RATE, MLP,error);
		for (unsigned int i = 1; i<MLP.size(); i++){
			MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}
		error = (MLP.at(3).GetOutput().at(0) - ((data[1][WINDOW_SIZE]-data[1][WINDOW_SIZE-1])/data[1][WINDOW_SIZE-1]));
		cout << (0.5*error*error) << endl;
	}

	cout << "Real value: " << data[1][WINDOW_SIZE] << endl;
	cout << "Predicted value: " << MLP.at(3).GetOutput().at(0)*data[1][WINDOW_SIZE-1]+data[1][WINDOW_SIZE-1] << endl;
	cout << "Difference: " << data[1][WINDOW_SIZE] - (MLP.at(3).GetOutput().at(0)*data[1][WINDOW_SIZE-1]+data[1][WINDOW_SIZE-1]) << endl;
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

Runner::~Runner()
{
}