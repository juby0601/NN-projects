#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>

class DataOut{
private:
	std::vector<std::vector<int> > data;
	std::string nameOfFile;
public:
	DataOut(std::string &input);
	int numberOfDays(int year, int month, int day);
	std::vector<std::vector<int> > getData(){return data;};
	~DataOut();
};

