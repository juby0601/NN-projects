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
	int NumberOfDays(int year, int month, int day);
	std::vector<std::vector<double> > GetData(){return data;};
	void PercentageChanges();
	~DataIn();
};

