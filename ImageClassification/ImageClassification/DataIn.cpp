#include "Config.h"
#include "DataIn.h"
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

DataIn::DataIn() {
	dataImages.resize(TOTAL_NUMBER_OF_CLASSES);

	for (int i = 1; i < 2; i++) {
	//for (int i = 1; i < 1/*INPUT_DATA_FILES*/; i++) {
		ReadData("data_batch_" + std::to_string(i) + ".bin");
	}

	LimitInput();
}

DataIn::~DataIn(){}

void DataIn::ReadData(std::string filename) {
	std::ifstream inputData(filename, std::ios::binary);
	std::vector<unsigned char> bufferData((
		std::istreambuf_iterator<char>(inputData)),
		(std::istreambuf_iterator<char>()));
	int typeData = 0;
	vector<double> emptyVector;
	emptyVector.resize(PIXELS_PER_COLOR_PER_IMAGE);

	for (int i = 0; i < bufferData.size(); i++) {
		if (i % TOTAL_VALUES_PER_IMAGE == 0) {
			typeData = bufferData.at(i);
			dataImages.at(bufferData.at(i)).push_back(emptyVector);
		}
		else {
			dataImages.at(typeData).at(dataImages.at(typeData).size() - 1).at((i - ((i / TOTAL_VALUES_PER_IMAGE) + 1)) % PIXELS_PER_COLOR_PER_IMAGE) += bufferData.at(i);
		}
	}
}

void DataIn::LimitInput() {
	for (int i = 0; i < TOTAL_NUMBER_OF_CLASSES; i++) {
		for (int j = 0; j < dataImages.at(i).size(); j++) {
			for (int k = 0; k < PIXELS_PER_COLOR_PER_IMAGE; k++) {
				dataImages.at(i).at(j).at(k) *= 0.00130718954248366004;
			}
		}
	}
}
