#include "Runner.h"
#include "Config.h"
#include "DataIn.h"
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
	vector<int> prediction = runner.PredictValues();

	int numberOfMissClassification = 0;
	for (int i = 0; i < prediction.size(); i++){
		if (prediction[i] != runner.GetDesiredOutput(i)){
			numberOfMissClassification++;
		}
	}
	cout << numberOfMissClassification;
	return 0;
};
