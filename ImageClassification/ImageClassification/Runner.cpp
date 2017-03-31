#include "Runner.h"
#include "Config.h"
#include "DataIn.h"
#include "Output.h"
#include <cstddef>

using namespace std;

Runner::Runner()
{
	MLP.resize(NUMBER_OF_LAYERS);
	string nameOfTheFile = "two_moon.txt";
	DataIn dataIn(nameOfTheFile);
	data = dataIn.GetData();
	Normalization();

	vector<double> coordinates;
	for (unsigned int i = 0; i < NUMBER_OF_INPUTS; i++){
		coordinates.push_back(data[i][0]);
	}
	MLP.at(0).InitInputlayer(NUMBER_OF_INPUTS, coordinates);
	MLP.at(0).ComputeOutputs();
	for (unsigned int i = 1; i<MLP.size(); i++){
		if (i == NUMBER_OF_LAYERS-1){
			MLP.at(i).Init(1,MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}else if (i == NUMBER_OF_LAYERS-2){
			MLP.at(i).Init(SECOND_HIDDEN_LAYER_NEURONS,MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}else{
			MLP.at(i).Init(FIRST_HIDDEN_LAYER_NEURONS,MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}
	}
	deltaWeights.resize(getNumberOfWeights());
}

void Runner::Normalization(){
	for (int i = 0; i < data[0].size(); i++){
		data[0][i] = (data[0][i] + XOFFSET)/XSCALE;
		data[1][i] = (data[1][i] + YOFFSET)/YSCALE;
	}
}

void Runner::Training(){
	double predictedClass;
	double error = 0;
	for (unsigned int f = 0; f < EPOCHS; f++){ 
		error = 0;
		for (unsigned int i = 0; i < TOTAL_WINDOW_SIZE; i++){
			predictedClass = PredictAValue(i);
			error += 0.5*(data[2][i]-predictedClass)*(data[2][i]-predictedClass);
			Backpropogation(LERANING_RATE,data[2][i]-predictedClass, predictedClass);
		}
		cout << "RMS: " <<error << endl;
	}
	cout << "Finished training" << endl;
	cout << endl;
}

double Runner::PredictAValue(int k){
	vector<double> coordinates(NUMBER_OF_INPUTS);
	for (unsigned int j = 0; j < NUMBER_OF_INPUTS; j++){
		coordinates[j] = data[j][k];
	}

	MLP.at(0).UpdateInputLayer(coordinates);
	MLP.at(0).ComputeOutputs();
	for (unsigned int i = 1; i<MLP.size(); i++){
		MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
		MLP.at(i).ComputeOutputs();
	}
	return (MLP.at(MLP.size() - 1).GetOutput().at(0));
}

vector<double> Runner::PredictValues(int start, int end) {
	vector<double> coordinates(NUMBER_OF_INPUTS);
	vector<double> predictedValues;
	double output;

	for (unsigned int k = start; k<end; k++){

		coordinates[0] = data[0][k];
		coordinates[1] = data[1][k];
								
		MLP.at(0).UpdateInputLayer(coordinates);
		MLP.at(0).ComputeOutputs();

		for (unsigned int i = 1; i<MLP.size(); i++){
			MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}
		output = MLP.at(MLP.size() - 1).GetOutput().at(0);
		if (output > 0.5){
			predictedValues.push_back(1);
		}else{
			predictedValues.push_back(0);
		}
	}
	return predictedValues;
}

void Runner::Backpropogation(double learningRate, double error, double out){
	vector<double> weightTemp;
	double errorSum = 0;
	double errorSumTemp = 0;
	double output = out;
	int deltaWeightCounter = 0;
	// Loop through layers
	for (int i = MLP.size()-1; i>=0; i--){
		// Loop through neurons in each layer
		for (unsigned int j = 0; j<MLP[i].LayerSize(); j++){
			weightTemp = MLP[i].GetNeuron(j).getWeights();
			if (i == (MLP.size()-1)){
				for (unsigned int k = 0; k<weightTemp.size(); k++){
					deltaWeights[deltaWeightCounter] = output*(1-output)*learningRate*MLP[i].GetInput()[k]*error+ALPHA*deltaWeights[deltaWeightCounter];
					weightTemp[k] += deltaWeights[deltaWeightCounter];
					errorSumTemp += weightTemp[k]*error*output*(1-output);
					deltaWeightCounter++;
				}
			}else{
				output = MLP[i].GetOutput()[j];
				for (unsigned int k = 0; k<weightTemp.size(); k++){
					deltaWeights[deltaWeightCounter] = output*(1-output)*learningRate*errorSum*MLP[i].GetInput()[k] + ALPHA*deltaWeights[deltaWeightCounter];
					weightTemp[k] += deltaWeights[deltaWeightCounter];
					errorSumTemp += weightTemp[k]*errorSum*output*(1-output);
					deltaWeightCounter++;
				}
			}
			MLP[i].GetNeuron(j).setWeights(weightTemp);
		}
		errorSum = errorSumTemp;
		errorSumTemp = 0;
	}
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
	return data[2][TOTAL_WINDOW_SIZE+k];
}


Runner::~Runner(){}