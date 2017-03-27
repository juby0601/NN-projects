#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>

class DataOut{
private:
	std::vector<std::vector<int> > stockPrice;
	std::string nameOfFile;
public:
	DataOut(std::string &input);
	~DataOut();
};

