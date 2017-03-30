#include "Runner.h"
#include "Config.h"
#include "DataIn.h"
#include "Input.h"
#include "Output.h"
#include <cstddef>
#include "Layer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
	srand (time(NULL));

	/*
	string nameOfTheFile = "two_moon.txt";
	DataIn dataIn(nameOfTheFile);
	vector< vector<double> >data = dataIn.GetData();

	for (int i = 0; i<data[1].size(); i++){
		for (int j = 0; j<3; j++){
			cout << data[j][i] << "			";
		}
		cout << endl;
	}*/

	//Runner runner;
	//runner.Training();
	//runner.Prediction(SAMPLE_SIZE-TOTAL_WINDOW_SIZE);

	//char exitInput;
	//cin >> exitInput;
	return 0;
};
