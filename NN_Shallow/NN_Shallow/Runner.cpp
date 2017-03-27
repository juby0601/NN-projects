#include "Runner.h"
#include "Config.h"
#include "DataIn.h"
#include "Input.h"
#include "HiddenLayer.h"
#include "Output.h"
#include "DataOut.h"
#include <cstddef>
#include "Layer.h"

using namespace std;

Runner::Runner()
{
}

void Runner::Training(){
	string nameOfTheFile = "StockPrice.txt";
	DataIn dataIn(nameOfTheFile);

	vector<vector<double> > data = dataIn.GetData();

	double result;
	
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
	cout << MLP.at(3).GetOutput().at(0) << endl;
	cout << MLP.at(3).GetOutput().at(0)*data[1][WINDOW_SIZE-1] + data[1][WINDOW_SIZE-1] << endl;
	cout << data[1][WINDOW_SIZE] << endl;
	cout << (MLP.at(3).GetOutput().at(0)*data[1][WINDOW_SIZE-1] + data[1][WINDOW_SIZE-1])-data[1][WINDOW_SIZE] << endl;
}

void Runner::Backpropogation(){

}

/*
  initialize network weights (often small random values)
  do
     forEach training example named ex
        prediction = neural-net-output(network, ex)  // forward pass
        actual = teacher-output(ex)
        compute error (prediction - actual) at the output units
        compute {\displaystyle \Delta w_{h}} \Delta w_h for all weights from hidden layer to output layer  // backward pass
        compute {\displaystyle \Delta w_{i}} \Delta w_i for all weights from input layer to hidden layer   // backward pass continued
        update network weights // input layer not modified by error estimate
  until all examples classified correctly or another stopping criterion satisfied
  return the network
*/

Runner::~Runner()
{
}