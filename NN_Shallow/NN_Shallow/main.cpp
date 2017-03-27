#include "Runner.h"

using namespace std;

int main() {
	DataOut dataOut;
	Input input;
	HiddenLayer hiddenLayers[HIDDEN_LAYERS];
	Output output;

	string nameOfTheFile = "StockPrice.txt";
	DataIn dataIn(nameOfTheFile);

	vector<vector<double> > data = dataIn.getData();

	for (unsigned int i = 0; i < data[1].size(); i++) {
		cout << data[0][i] << "		";
		cout << data[1][i] << "		";
		cout << data[2][i] << endl; 
	}

	char exitInput;
	cin >> exitInput;
	return 0;
};
