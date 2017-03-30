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

	Runner runner;

	runner.Training();
	int errorCounter = 0;
	vector<double> prediction = runner.PredictValues(TOTAL_WINDOW_SIZE,SAMPLE_SIZE);
	for (int i = 0; i<prediction.size(); i++){
		cout << "Predicted class: " << prediction[i] << "  vs  ";
		cout << "Real class: " << runner.getDesiredOutput(i) << endl;
		if (prediction[i] != runner.getDesiredOutput(i)){
			errorCounter++;
		}
	}
	cout << "Total number of errors:  " << errorCounter << endl;

	return 0;
};
