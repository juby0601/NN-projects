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

int main() {
	srand (time(NULL));

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
	runner.Prediction(10);

	char exitInput;
	cin >> exitInput;
	return 0;
};
