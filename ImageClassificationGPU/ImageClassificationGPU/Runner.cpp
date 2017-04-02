#include "Runner.h"
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
	initialImage = af::reorder(data(0,0,span),2,0,1,3);		
	MLP.at(0).InitInputlayer(NUMBER_OF_INPUTS, initialImage);
	MLP.at(0).ComputeOutputsInputLayer();
	for (unsigned int i = 1; i<MLP.size(); i++){
		MLP.at(i).Init(LAYER_NEURONS[i], MLP.at(i - 1).GetOutput());
		MLP.at(i).ComputeOutputs();
	}
}

void Runner::Training() {
	af::array predictedClasses;
	af::array correctOutput = af::constant(0, TOTAL_NUMBER_OF_CLASSES, f64);
	af::array RMSerrorTemp;
	af::array RMSerror = af::constant(0, 1, f64);
	af::array error;
	//for (unsigned int f = 0; f < EPOCHS; f++){
	gfor (seq f, 0,EPOCHS) {
		for (unsigned int i = 0; i < TOTAL_NUMBER_OF_IMAGES; i++) {
		//gfor (seq i, 0,1,TOTAL_NUMBER_OF_IMAGES){
			for (unsigned j = 0; j < TOTAL_NUMBER_OF_CLASSES; j++) {
			//gfor (seq j, 0,1,TOTAL_NUMBER_OF_CLASSES){
				correctOutput(j) = 1;
				predictedClasses = PredictAValue(j,i);
				error = correctOutput - predictedClasses;
				RMSerrorTemp = 0.5*error*error;
				RMSerror(0) = RMSerror(0)+af::sum(RMSerrorTemp);
				Backpropogation(error, predictedClasses);	
				correctOutput(j) = 0;
			}
		}
		cout << "RMS: " << (double)RMSerror.scalar<double>() << endl;
		RMSerror(0) = 0;
	}
	cout << "Finished training" << endl;
	cout << endl;
}

af::array Runner::PredictAValue(int classType, int imageNr){
	af::array imagePixels = af::array(NUMBER_OF_INPUTS);
	imagePixels = af::reorder(data(classType, imageNr, span), 2, 0, 1, 3);
	MLP.at(0).UpdateInputLayer(imagePixels);
	MLP.at(0).ComputeOutputsInputLayer();
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
		MLP.at(0).ComputeOutputsInputLayer();

		for (unsigned int i = 1; i<MLP.size(); i++){
			MLP.at(i).UpdateLayer(MLP.at(i-1).GetOutput());
			MLP.at(i).ComputeOutputs();
		}
		af::max(value, index, MLP.at(MLP.size() - 1).GetOutput(), 0);
		predictedValues(i) = index.scalar<int>();
	}
	return predictedValues;
}

void Runner::Backpropogation(af::array &error, af::array &out){
	af::array weightTemp;
	af::array errorSum = af::array(1);
	af::array output;

	// Loop through layers	
	for (int i = MLP.size()-1; i>=0; i--){

		if (i == (MLP.size()-1)){
			output = MLP[i].GetOutput();
			MLP[i].GetDeltaWeights() = LERANING_RATE*af::matmulNT(MLP[i].GetInput(),(error*output*(1-output))) + ALPHA*MLP[i].GetDeltaWeights();
			MLP[i].GetWeights() += MLP[i].GetDeltaWeights();
			errorSum = af::sum(af::matmulTT((error*output*(1-output)),MLP[i].GetWeights()));
		}else if (i == 0) {
			output = MLP[i].GetOutput();
			MLP[i].GetDeltaWeights() = LERANING_RATE*(errorSum.scalar<double>()*MLP[i].GetInput()*(output*(1 - output))) + ALPHA*MLP[i].GetDeltaWeights();
			MLP[i].GetWeights() += MLP[i].GetDeltaWeights();
		}else{
			output = MLP[i].GetOutput();
			MLP[i].GetDeltaWeights() = LERANING_RATE*(errorSum.scalar<double>()*af::matmulNT(MLP[i].GetInput(), (output*(1 - output)))) +ALPHA*MLP[i].GetDeltaWeights();
			MLP[i].GetWeights() += MLP[i].GetDeltaWeights();
			errorSum = errorSum(0)*af::sum(af::matmulTT((output*(1-output)),MLP[i].GetWeights()));
		}
	}	
}

af::array Runner::GetDesiredOutput(int k){
	return testData(k, 0);
}


Runner::~Runner(){}
