#include "Config.h"
#include "DataIn.h"
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

DataIn::DataIn() {
	// Type -> Image -> Pixels
	vector<vector<vector<double>>> dataImages;
	dataImages.resize(TOTAL_NUMBER_OF_CLASSES);

	// Image -> (Type + Pixels)
	vector<vector<vector<double>>> testObjects;

	std::ifstream inputData1("data_batch_1.bin", std::ios::binary);
	/*std::ifstream inputData2("data_batch_2.bin", std::ios::binary);
	std::ifstream inputData3("data_batch_3.bin", std::ios::binary);
	std::ifstream inputData4("data_batch_4.bin", std::ios::binary);
	std::ifstream inputData5("data_batch_5.bin", std::ios::binary);
	std::ifstream inputTest("test_batch.bin", std::ios::binary);*/

	std::vector<char> bufferData1((
		std::istreambuf_iterator<char>(inputData1)),
		(std::istreambuf_iterator<char>()));
	/*std::vector<char> bufferData2((
		std::istreambuf_iterator<char>(inputData2)),
		(std::istreambuf_iterator<char>()));
	std::vector<char> bufferData3((
		std::istreambuf_iterator<char>(inputData3)),
		(std::istreambuf_iterator<char>()));
	std::vector<char> bufferData4((
		std::istreambuf_iterator<char>(inputData4)),
		(std::istreambuf_iterator<char>()));
	std::vector<char> bufferData5((
		std::istreambuf_iterator<char>(inputData5)),
		(std::istreambuf_iterator<char>()));
	std::vector<char> bufferTest((
		std::istreambuf_iterator<char>(inputTest)),
		(std::istreambuf_iterator<char>()));
	cout << bufferData1.size() << endl;
	cout << bufferData2.size() << endl;
	cout << bufferData3.size() << endl;
	cout << bufferData4.size() << endl;
	cout << bufferData5.size() << endl;*/

	int typeData1 = 0;
	/*int typeData2 = 0;
	int typeData3 = 0;
	int typeData4 = 0;
	int typeData5 = 0;*/
	vector<double> emptyVector;
	emptyVector.resize(PIXELS_PER_COLOR_PER_IMAGE);

	for (int i = 0; i < bufferData1.size(); i++) {
		if (i % TOTAL_VALUES_PER_IMAGE == 0) {
			typeData1 = bufferData1.at(i);
			/*typeData2 = bufferData2.at(i);
			typeData3 = bufferData3.at(i);
			typeData4 = bufferData4.at(i);
			typeData5 = bufferData5.at(i);*/

			dataImages.at(bufferData1.at(i)).push_back(emptyVector);
			/*dataImages.at(bufferData2.at(i)).push_back(emptyVector);
			dataImages.at(bufferData3.at(i)).push_back(emptyVector);
			dataImages.at(bufferData4.at(i)).push_back(emptyVector);
			dataImages.at(bufferData5.at(i)).push_back(emptyVector);*/
		}
		else {
			dataImages.at(typeData1).at(dataImages.at(typeData1).size() - 1).at((i - ((i + 1) % TOTAL_VALUES_PER_IMAGE)) % PIXELS_PER_COLOR_PER_IMAGE) += bufferData1.at(i);
			/*dataImages.at(typeData2 - 1).at(dataImages.at(typeData2 - 1).size() - 1).at((i - ((i + 1) % TOTAL_VALUES_PER_IMAGE)) % PIXELS_PER_COLOR_PER_IMAGE) += bufferData2.at(i);
			dataImages.at(typeData3 - 1).at(dataImages.at(typeData3 - 1).size() - 1).at((i - ((i + 1) % TOTAL_VALUES_PER_IMAGE)) % PIXELS_PER_COLOR_PER_IMAGE) += bufferData3.at(i);
			dataImages.at(typeData4 - 1).at(dataImages.at(typeData4 - 1).size() - 1).at((i - ((i + 1) % TOTAL_VALUES_PER_IMAGE)) % PIXELS_PER_COLOR_PER_IMAGE) += bufferData4.at(i);
			dataImages.at(typeData5 - 1).at(dataImages.at(typeData5 - 1).size() - 1).at((i - ((i + 1) % TOTAL_VALUES_PER_IMAGE)) % PIXELS_PER_COLOR_PER_IMAGE) += bufferData5.at(i);*/
		}
	}

	// Limit pixel values to be between 0 and 1
	for (int i = 0; i < TOTAL_NUMBER_OF_CLASSES; i++) {
		for (int j = 0; j < dataImages.at(i).size(); j++) {
			for (int k = 0; k < PIXELS_PER_COLOR_PER_IMAGE; k++) {
				dataImages.at(i).at(j).at(k) *= 0.00130718954248366004;
			}
		}
	}
}

DataIn::~DataIn(){}
