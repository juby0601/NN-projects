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
	runner.Prediction(SAMPLE_SIZE-TOTAL_WINDOW_SIZE);

	//char exitInput;
	//cin >> exitInput;
	return 0;
};
