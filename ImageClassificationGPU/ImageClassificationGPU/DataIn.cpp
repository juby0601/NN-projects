#include "Config.h"
#include "DataIn.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <cstdlib>
using namespace std;
using namespace af;

DataIn::DataIn() {
	dataImages = af::array(TOTAL_NUMBER_OF_CLASSES, TOTAL_NUMBER_OF_IMAGES, PIXELS_PER_COLOR_PER_IMAGE, f64);
	testObjects = af::array(TOTAL_NUMBER_OF_TEST_IMAGES, PIXELS_PER_COLOR_PER_IMAGE, f64);

	stringstream ss;
	for (int i = 1; i < 6; i++) {
		ss.str("");
		ss << i;
		convertData(ReadData("data_batch_" + ss.str() + ".bin"));
	}

	vector<unsigned char> bufferTest = ReadData("test_batch.bin");
	//Creating test objects
	double red,blue,green;
	for (int i = 0; i<TOTAL_NUMBER_OF_TEST_IMAGES; i++){
		testObjects(i, 0) = (double)bufferTest[i*TOTAL_VALUES_PER_IMAGE];
		for (int j = 1; j<PIXELS_PER_COLOR_PER_IMAGE+1; j++){
			red = (double)bufferTest[TOTAL_VALUES_PER_IMAGE*i+j];
			blue = (double)bufferTest[TOTAL_VALUES_PER_IMAGE*i+j+PIXELS_PER_COLOR_PER_IMAGE];
			green = (double)bufferTest[TOTAL_VALUES_PER_IMAGE*i+j+2*PIXELS_PER_COLOR_PER_IMAGE];
			testObjects(i, j) = (red + blue + green) / (3 * 255);
		}
	}
}

void DataIn::convertData(vector<unsigned char> input){
	int objectCounter = 0;
	double red,blue,green;
	vector<double> images;
	vector<int> imageCounter(10,0);
	for (int i = 0; i<TOTAL_NUMBER_OF_TEST_IMAGES; i++){
		for (int j = 1; j<PIXELS_PER_COLOR_PER_IMAGE+1; j++){
			unsigned int k = TOTAL_VALUES_PER_IMAGE * i;
			red = (double)input[k+j];
			blue = (double)input[k+j+PIXELS_PER_COLOR_PER_IMAGE];
			green = (double)input[k+j+2*PIXELS_PER_COLOR_PER_IMAGE];
			dataImages((int)input[k], imageCounter[(int)input[k]],j-1) = (red + blue + green) / (3 * 255);
			imageCounter[(int)input[k]]++;
		}
	}
}

vector<unsigned char> DataIn::ReadData(string filename) {
	cout << "Loading: " << filename << endl;
	std::ifstream inputData(filename.c_str(), std::ios::binary);
	inputData.unsetf(std::ios::skipws);
	std::streampos fileSize;

    inputData.seekg(0, std::ios::end);
    fileSize = inputData.tellg();
    inputData.seekg(0, std::ios::beg);

    vector<unsigned char> bufferData;
    bufferData.reserve(fileSize);
    bufferData.insert(bufferData.begin(), std::istream_iterator<unsigned char>(inputData), std::istream_iterator<unsigned char>());

	return bufferData;
}

DataIn::~DataIn(){}
