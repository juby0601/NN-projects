
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

	vector<vector<int> > data = dataOut.getData();

	for (unsigned int i = 0; i < data[1].size(); i++) {
		cout << data[0][i] << "		";
		cout << data[1][i] << endl; 
	}

	char exitInput;
	cin >> exitInput;
	return 0;
}
;