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
	imageCounter.resize(TOTAL_NUMBER_OF_CLASSES);
	dataImages = af::array(TOTAL_NUMBER_OF_CLASSES, TOTAL_NUMBER_OF_IMAGES, PIXELS_PER_COLOR_PER_IMAGE, f64);
	testObjects = af::array(TOTAL_NUMBER_OF_TEST_IMAGES, PIXELS_PER_COLOR_PER_IMAGE, f64);

	stringstream ss;
	for (int i = 1; i < 6; i++) {
		ss.str("");
		ss << i;
		convertData(ReadData("data_batch_" + ss.str() + ".bin"));
	}

	af::array bufferTest = ReadData("test_batch.bin");

	af::dim4 newDim(TOTAL_VALUES_PER_IMAGE, TOTAL_NUMBER_OF_TEST_IMAGES);
	af::array inputMatrix = af::moddims(bufferTest, newDim);
	inputMatrix.rows(1, PIXELS_PER_COLOR_PER_IMAGE) = (inputMatrix.rows(1, PIXELS_PER_COLOR_PER_IMAGE) + inputMatrix.rows(PIXELS_PER_COLOR_PER_IMAGE + 1, 2 * PIXELS_PER_COLOR_PER_IMAGE) + inputMatrix.rows(2 * PIXELS_PER_COLOR_PER_IMAGE + 1, 3 * PIXELS_PER_COLOR_PER_IMAGE)) / (double)(3 * 255);
	testObjects = inputMatrix.rows(0, PIXELS_PER_COLOR_PER_IMAGE);
}

void DataIn::convertData(af::array &input){
	af::dim4 newDim(TOTAL_VALUES_PER_IMAGE, TOTAL_NUMBER_OF_TEST_IMAGES);
	af::array inputMatrix = af::moddims(input, newDim);
	af::array classes = inputMatrix.row(0);
	af::array intensity = (inputMatrix.rows(1, PIXELS_PER_COLOR_PER_IMAGE) + inputMatrix.rows(PIXELS_PER_COLOR_PER_IMAGE+1, 2 * PIXELS_PER_COLOR_PER_IMAGE) + inputMatrix.rows(2 * PIXELS_PER_COLOR_PER_IMAGE+1,3 * PIXELS_PER_COLOR_PER_IMAGE)) / (double)(3 * 255);
	vector<int> imageCounter(10, 0);
	char *classIndex = new char[10000];
	classes.host(classIndex);
	for (int i = 0; i<TOTAL_NUMBER_OF_TEST_IMAGES; i++) {
		dataImages((int)classIndex[i], imageCounter[classIndex[i]], span) = intensity.col(i);
		imageCounter[classIndex[i]] = imageCounter[classIndex[i]] +1;
	}
	delete[] classIndex;
}

af::array DataIn::ReadData(string filename) {
	cout << "Loading: " << filename << endl;
	
	std::basic_ifstream<unsigned char> binaryIo;
	unsigned char* bufferTemp = 0;
	size_t size = 0;
	binaryIo.open(filename, ios::in | ios::binary);
	if (binaryIo.is_open()) {
		binaryIo.seekg(0, ios::end);
		size = binaryIo.tellg();
		binaryIo.seekg(0, ios::beg);

		bufferTemp = new unsigned char[TOTAL_VALUES_PER_IMAGE * TOTAL_NUMBER_OF_TEST_IMAGES];
		binaryIo.read(bufferTemp, size);
	}

	af::array output(TOTAL_VALUES_PER_IMAGE * TOTAL_NUMBER_OF_TEST_IMAGES, bufferTemp);
	delete[] bufferTemp;
	return output;
}

DataIn::~DataIn(){}
