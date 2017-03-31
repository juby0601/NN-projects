#include "DataIn.h"
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

DataIn::DataIn() {
	int length;
	char * buffer;
	vector<double> colorValues;

	std::ifstream inputData1("data_batch_1.bin", std::ios::binary);
	std::ifstream inputData2("data_batch_2.bin", std::ios::binary);
	std::ifstream inputData3("data_batch_3.bin", std::ios::binary);
	std::ifstream inputData4("data_batch_4.bin", std::ios::binary);
	std::ifstream inputData5("data_batch_5.bin", std::ios::binary);
	std::ifstream inputTest("test_batch.bin", std::ios::binary);

	std::vector<char> bufferData1((
		std::istreambuf_iterator<char>(inputData1)),
		(std::istreambuf_iterator<char>()));
	std::vector<char> bufferData2((
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

	for (int i = 0; i < bufferData1.size(); i++) {
		cout << bufferData1.at(i) << endl;
	}
	cout << bufferData1.size() << endl;
}


DataIn::~DataIn(){}
