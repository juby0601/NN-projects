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
#define isequal(a, b) af::alltrue<bool>((a) == (b))

int main() {

	srand (time(NULL));

	Runner runner;
	runner.Training();
	af::array prediction = runner.PredictValues();

	int numberOfMissclassifications = 0;
	for (int i = 0; i < prediction.dims(0); i++){
		if (isequal(prediction(i),runner.GetDesiredOutput(i))){
			numberOfMissclassifications++;
		}
	}
	cout << numberOfMissclassifications;

	return 0;
};
