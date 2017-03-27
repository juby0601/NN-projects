
#include "DataIn.h"
#include "Input.h"
#include "HiddenLayer.h"
#include "Output.h"
#include "DataOut.h"

using namespace std;

int main() {

	const int HIDDEN_LAYERS = 1;
	HiddenLayer hiddenLayers[HIDDEN_LAYERS];
	DataIn dataIn;
	Input input;
	Output output;

	string nameOfTheFile = "StockPrice.txt";
	DataOut dataOut(nameOfTheFile);

	char exitInput;
	cin >> exitInput;
	return 0;
}
;