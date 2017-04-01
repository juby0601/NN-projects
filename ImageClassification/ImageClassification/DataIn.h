#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>
#include<stdlib.h>

class DataIn{
public:
	DataIn();
	std::vector<std::vector<std::vector<double> > > GetTrainingData(){return dataImages;};
	std::vector<std::vector<double> > GetTestData(){return testObjects;}
	~DataIn();

private:
	// Type -> Image -> Pixels
	std::vector<std::vector<std::vector<double> > > dataImages;
	// Image -> (Type + Pixels)
	std::vector<std::vector<double> > testObjects;
	void convertData(std::vector<unsigned char> input);
	std::vector<unsigned char> ReadData(std::string filename);
};
