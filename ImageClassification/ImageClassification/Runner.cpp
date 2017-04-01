#include "Runner.h"
#include "Config.h"
#include "DataIn.h"
#include "Output.h"
#include <cstddef>

using namespace std;

Runner::Runner() {

	MLP.resize(NUMBER_OF_LAYERS);
	DataIn dataIn;
	data = dataIn.GetTrainingData();
	testData = dataIn.GetTestData();
	vector<double> initialImage;
	for (unsigned int i = 0; i < NUMBER_OF_INPUTS; i++){
		initialImage.push_back(data[0][0][i]);
	}
	MLP.at(0).InitInputlayer(NUMBER_OF_INPUTS, initialImage);
	MLP.at(0).ComputeOutputs();
	for (unsigned int i = 1; i<MLP.size(); i++){
		if (i == NUMBER_OF_LAYERS-1){
			MLP.at(i).Init(OUTPUT_NEURONS,MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}else if (i == NUMBER_OF_LAYERS-2){
			MLP.at(i).Init(SECOND_HIDDEN_LAYER_NEURONS,MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}else{
			MLP.at(i).Init(FIRST_HIDDEN_LAYER_NEURONS,MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}
	}
	deltaWeights.resize(GetNumberOfWeights());
}

void Runner::Training(){
	vector<double> predictedClasses;
	vector<double> correctOutput(10,0);
	double RMSerror = 0;
	vector<double> error(OUTPUT_NEURONS);
	for (unsigned int f = 0; f < EPOCHS; f++){ 
		for (unsigned int i = 0; i < TOTAL_NUMBER_OF_CLASSES; i++){
			correctOutput[i] = 1;
			for (unsigned j = 0; j < TOTAL_NUMBER_OF_IMAGES; j++){
				predictedClasses = PredictAValue(i,j);
				for (unsigned int k =0; k < TOTAL_NUMBER_OF_CLASSES; k++){
					RMSerror += 0.5*(correctOutput[k]-predictedClasses[k])*(correctOutput[k]-predictedClasses[k]);
					error[k] = (correctOutput[k]-predictedClasses[k]);
					cout << (correctOutput[k]-predictedClasses[k]) << endl;
				}
				cout << endl;
				Backpropogation(LERANING_RATE,error, predictedClasses);	
				if (j % 5000 == 0){
					cout << "RMS: " << RMSerror << endl;
					RMSerror = 0;
				}
			}
			correctOutput[i] = 0;
		}
	}
	cout << "Finished training" << endl;
	cout << endl;
}

vector<double> Runner::PredictAValue(int classType, int imageNr){
	vector<double> output(OUTPUT_NEURONS);
	vector<double> imagePixels(NUMBER_OF_INPUTS);
	for (unsigned int j = 0; j < NUMBER_OF_INPUTS; j++){
		imagePixels[j] = data[classType][imageNr][j];
	}
	MLP.at(0).UpdateInputLayer(imagePixels);
	MLP.at(0).ComputeOutputs();
	for (unsigned int i = 1; i<MLP.size(); i++){
		MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
		MLP.at(i).ComputeOutputs();
	}
	for (int i = 0; i<OUTPUT_NEURONS; i++){
		output[i] = (MLP.at(MLP.size() - 1).GetOutput().at(i));
	}

	return output;
}

vector<int> Runner::PredictValues() {
	vector<double> testImage(NUMBER_OF_INPUTS);
	vector<int> predictedValues;
	double output;

	for (unsigned int i= 0; i < TOTAL_NUMBER_OF_IMAGES; i++){
		for (unsigned int j = 1; j < NUMBER_OF_INPUTS+1; j++){
			testImage[j-1] = testData[i][j];
		}
		MLP.at(0).UpdateInputLayer(testImage);
		MLP.at(0).ComputeOutputs();

		for (unsigned int i = 1; i<MLP.size(); i++){
			MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}

		predictedValues.push_back(FindIndexOfMax(MLP.at(MLP.size()-1).GetOutput()));
	}
	return predictedValues;
}

int Runner::FindIndexOfMax(vector<double> input){
	int output;
	double currentMax = -1;
	for (int i = 0; i<(input.size()-1); i++){
		if (input[i] > currentMax){
			output = i;
			currentMax = input[i];
		}
	}	
	return output;
}

void Runner::Backpropogation(double learningRate, vector<double> error, vector<double> out){
	vector<double> weightTemp;
	double errorSum = 0;
	double errorSumTemp = 0;
	double output;
	int deltaWeightCounter = 0;
	// Loop through layers
	for (int i = MLP.size()-1; i>=0; i--){
		// Loop through neurons in each layer
		for (unsigned int j = 0; j<MLP[i].LayerSize(); j++){
			weightTemp = MLP[i].GetNeuron(j).getWeights();

			if (i == (MLP.size()-1)){
				output = out[j];
				for (unsigned int k = 0; k<weightTemp.size(); k++){
					deltaWeights[deltaWeightCounter] = output*(1-output)*learningRate*MLP[i].GetInput()[k]*error[j]+ALPHA*deltaWeights[deltaWeightCounter];
					weightTemp[k] += deltaWeights[deltaWeightCounter];
					errorSumTemp += weightTemp[k]*error[j]*output*(1-output);
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

int Runner::GetNumberOfWeights(){
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


double Runner::GetDesiredOutput(int k){
	return testData[k][0];
}


Runner::~Runner(){}