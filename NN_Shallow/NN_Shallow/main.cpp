
#include "Config.h"
#include "DataIn.h"
#include "Input.h"
#include "HiddenLayer.h"
#include "Output.h"
#include "DataOut.h"

using namespace std;

int main() {
	DataIn dataIn;
	Input input;
	HiddenLayer hiddenLayers[HIDDEN_LAYERS];
	Output output;

	string nameOfTheFile = "StockPrice.txt";
	DataOut dataOut(nameOfTheFile);

	char exitInput;
	cin >> exitInput;
	return 0;
}
;