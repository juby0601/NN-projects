#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>
#include<stdlib.h>
#include<arrayfire.h>

class DataIn{
public:
	DataIn();
	af::array GetTrainingData(){return dataImages;};
	af::array GetTestData(){return testObjects;}
	~DataIn();

private:
	// Type -> Image -> Pixels
	af::array dataImages;
	// Image -> (Type + Pixels)
	af::array testObjects;
	void convertData(af::array &input);
	af::array ReadData(std::string filename);
	std::vector<int> imageCounter;
};
