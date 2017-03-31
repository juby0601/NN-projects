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
	~DataIn();
	/*int NumberOfDays(int year, int month, int day);
	std::vector<std::vector<double> > GetData(){return data;};
	void PercentageChanges();*/

private:
	void ReadData(std::string fileName);
	void LimitInput();

	std::vector<std::vector<std::vector<double>>> dataImages; // Type -> Image -> Pixels
	std::vector<std::vector<std::vector<double>>> testObjects; // Image -> (Type + Pixels)
};
