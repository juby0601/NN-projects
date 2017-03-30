#include "Runner.h"
#include "Config.h"
#include "DataIn.h"
#include "Input.h"
#include "HiddenLayer.h"
#include "Output.h"
#include "DataOut.h"
#include <cstddef>
#include "Layer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
	srand (time(NULL));
	int predictionT = 10;
	/*
	string nameOfTheFile = "StockPrice.txt";
	DataIn dataIn(nameOfTheFile);

	vector<vector<double> > data = dataIn.GetData();

	for (unsigned int i = 0; i < data[1].size(); i++) {
		cout << data[0][i] << "		";
		cout << data[1][i] << "		";
		cout << data[2][i] << endl; 
	}*/

	Runner runner;
	runner.Training();
	runner.Prediction(SAMPLE_SIZE-TOTAL_WINDOW_SIZE);
/*	for (int i = 0; i<5; i++){

	cout << "Real value: " << runner.getDesiredOutput(predictionT*i + predictionT) << endl;
	cout << "Predicted value: " << runner.PredictAValue(predictionT*i + predictionT) << endl;
	cout << "Error: " << (runner.getDesiredOutput(predictionT*i + predictionT)-runner.PredictAValue(predictionT*i + predictionT))/runner.getDesiredOutput(predictionT*i + predictionT)*100 << endl;
	cout << endl;

	}
	*/



	//char exitInput;
	//cin >> exitInput;
	return 0;
};
