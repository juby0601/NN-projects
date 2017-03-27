#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>

class DataIn{
private:
	std::vector<std::vector<double> > data;
	std::string nameOfFile;
public:
	DataIn(std::string &input);
	int numberOfDays(int year, int month, int day);
	std::vector<std::vector<double> > getData(){return data;};
	void percentageChanges();
	~DataIn();
};

