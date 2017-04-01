#include "Config.h"
#include "DataIn.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>
using namespace std;

DataIn::DataIn() {
	dataImages.resize(TOTAL_NUMBER_OF_CLASSES);
	testObjects.resize(TOTAL_NUMBER_OF_TEST_IMAGES);
	stringstream ss;
	for (int i = 1; i < 6; i++) {
		ss.str("");
		ss << i;
		convertData(ReadData("data_batch_" + ss.str() + ".bin"));
	}

	vector<unsigned char> bufferTest = ReadData("test_batch.bin");
	//Creating test objects
	int testObjectCounter = 0;
	double red,blue,green;
	for (int i = 0; i<TOTAL_NUMBER_OF_TEST_IMAGES; i++){
		testObjects.at(i).push_back((double)bufferTest[i*TOTAL_VALUES_PER_IMAGE]);
		for (int j = 1; j<PIXELS_PER_COLOR_PER_IMAGE+1; j++){
			red = (double)bufferTest[TOTAL_VALUES_PER_IMAGE*i+j];
			blue = (double)bufferTest[TOTAL_VALUES_PER_IMAGE*i+j+PIXELS_PER_COLOR_PER_IMAGE];
			green = (double)bufferTest[TOTAL_VALUES_PER_IMAGE*i+j+2*PIXELS_PER_COLOR_PER_IMAGE];
			testObjects.at(i).push_back((red+blue+green)/(3*255));
		}
	}
}

void DataIn::convertData(vector<unsigned char> input){
	int objectCounter = 0;
	double red,blue,green;
	vector<double> images;
	for (int i = 0; i<TOTAL_NUMBER_OF_TEST_IMAGES; i++){
		dataImages.at((int)input[i*TOTAL_VALUES_PER_IMAGE]).push_back(images);
		for (int j = 1; j<PIXELS_PER_COLOR_PER_IMAGE+1; j++){
			red = (double)input[TOTAL_VALUES_PER_IMAGE*i+j];
			blue = (double)input[TOTAL_VALUES_PER_IMAGE*i+j+PIXELS_PER_COLOR_PER_IMAGE];
			green = (double)input[TOTAL_VALUES_PER_IMAGE*i+j+2*PIXELS_PER_COLOR_PER_IMAGE];
			int lastElement = dataImages.at((int)input[i*TOTAL_VALUES_PER_IMAGE]).size()-1;
			dataImages.at((int)input[i*TOTAL_VALUES_PER_IMAGE]).at(lastElement).push_back((red+blue+green)/(3*255));
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
