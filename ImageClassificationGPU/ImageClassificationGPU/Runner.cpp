﻿#include "Runner.h"
#include "Config.h"
#include "DataIn.h"
#include "Output.h"
#include <cstddef>

using namespace std;
using namespace af;

Runner::Runner() {

	MLP.resize(NUMBER_OF_LAYERS);
	DataIn dataIn;
	data = dataIn.GetTrainingData();
	testData = dataIn.GetTestData();
	af::array initialImage = af::array(PIXELS_PER_COLOR_PER_IMAGE, f64);
	initialImage = data(0,0,span);	
	/*	
	for (unsigned int i = 0; i < NUMBER_OF_INPUTS; i++){
		initialImage(i) = data(0,0,i);
	}
	*/
	MLP.at(0).InitInputlayer(NUMBER_OF_INPUTS, initialImage);
	MLP.at(0).ComputeOutputs();
	for (unsigned int i = 1; i<MLP.size(); i++){
		MLP.at(i).Init(LAYER_NEURONS[i], MLP.at(i - 1).GetOutput());
		MLP.at(i).ComputeOutputs();
	}
}

void Runner::Training(){
	af::array predictedClasses;
	af::array correctOutput = af::constant(0, TOTAL_NUMBER_OF_CLASSES, f64);
	af::array RMSerror;
	af::array error;
	for (unsigned int f = 0; f < EPOCHS; f++){
		
		for (unsigned int i = 0; i < TOTAL_NUMBER_OF_IMAGES; i++){
			for (unsigned j = 0; j < TOTAL_NUMBER_OF_CLASSES; j++){
				correctOutput(j) = 1;
				predictedClasses = PredictAValue(j,i);

				error = correctOutput - predictedClasses;
				RMSerror = 0.5*error*error;
				RMSerror += af::sum(RMSerror);

				Backpropogation(LERANING_RATE,error, predictedClasses);	
				correctOutput(j) = 0;
			}
			if (i % 5000 == 0) {
				cout << "RMS: " << RMSerror.scalar<float>() << endl;
				RMSerror = 0;
			}
		}
	}
	cout << "Finished training" << endl;
	cout << endl;
}

af::array Runner::PredictAValue(int classType, int imageNr){
	af::array imagePixels = af::array(NUMBER_OF_INPUTS);
	imagePixels = data(classType, imageNr, span);	
	/*
	for (unsigned int j = 0; j < NUMBER_OF_INPUTS; j++){
		imagePixels(j) = data(classType,imageNr,j);
	}
	*/
	MLP.at(0).UpdateInputLayer(imagePixels);
	MLP.at(0).ComputeOutputs();
	for (unsigned int i = 1; i<MLP.size(); i++){
		MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
		MLP.at(i).ComputeOutputs();
	}

	return MLP.at(MLP.size() - 1).GetOutput();
}

af::array Runner::PredictValues() {
	af::array testImage(NUMBER_OF_INPUTS);
	af::array predictedValues = af::array(TOTAL_NUMBER_OF_IMAGES, s32);
	af::array index;
	af::array value;

	for (unsigned int i= 0; i < TOTAL_NUMBER_OF_IMAGES; i++){
		for (unsigned int j = 1; j < NUMBER_OF_INPUTS+1; j++){
			testImage(j-1) = testData(i,j);
		}
		MLP.at(0).UpdateInputLayer(testImage);
		MLP.at(0).ComputeOutputs();

		for (unsigned int i = 1; i<MLP.size(); i++){
			MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}
		af::max(value, index, MLP.at(MLP.size() - 1).GetOutput(), 0);
		predictedValues(i) = index.scalar<int>();
	}
	return predictedValues;
}

void Runner::Backpropogation(double learningRate, af::array &error, af::array &out){
	
	af::array weightTemp;
	af::array errorSum(1,f64);
	af::array errorSumTemp(1,f64);
	af::array output;

	// Loop through layers	
	for (int i = MLP.size()-1; i>=0; i--){

		if (i == (MLP.size()-1)){
			output = MLP[i].GetOutput();
			MLP[i].GetDeltaWeights() = learningRate*af::matmulNT(MLP[i].GetInput,(error*output*(1-output))) + ALPHA*MLP[i].GetDeltaWeights();
			MLP[i].GetWeights() += MLP[i].GetDeltaWeights();
			errorSumTemp(0) += af::sum(af::matmulTT((error*output*(1-output)),MLP[i].GetWeights()));
		}else{
			output = MLP[i].GetOutput();
			MLP[i].GetDeltaWeights() = errorSum.scalar()*learningRate*af::matmulNT(MLP[i].GetInput,(output*(1-output))) + ALPHA*MLP[i].GetDeltaWeights();
			MLP[i].GetWeights() += MLP[i].GetDeltaWeights();
			errorSumTemp(0) += errorSum.scalar()*af::sum(af::matmulTT((output*(1-output)),MLP[i].GetWeights()));	
		}
		errorSum(0) = errorSumTemp.scalar();
		errorSumTemp(0) = 0;
	}	
}

int Runner::GetNumberOfWeights(){
	int numberOfWeights = 0;
	for (int i = MLP.size()-1; i>=0; i--){
		for (unsigned int j = 0; j<MLP[i].LayerSize(); j++){
			for (unsigned int k = 0; k<MLP[i].GetWeights().dims(0); k++){
				//cout << MLP[i].GetWeights()(k,j) << " ";
				numberOfWeights++;
			}
			//cout << endl;
		}
	}
	cout << numberOfWeights << endl;
	return numberOfWeights;
}


double Runner::GetDesiredOutput(int k){
	return testData[k][0];
}


Runner::~Runner(){}
