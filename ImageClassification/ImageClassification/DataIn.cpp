#include "DataIn.h"
using namespace std;

DataIn::DataIn(string &input)
{
	vector<double> xCoor;
	vector<double> yCoor;
	vector<double> classNr;
	string line;
	ifstream moonData;

	double xCoorDouble, yCoorDouble, classNrDouble;
    string xCoorString,yCoorString,classNrString;

	int numberOfIterations = 1;
	moonData.open(input.c_str());

	if (moonData.is_open()){
    	while ( getline (moonData,line) ){
    		stringstream sentence(line);

    		if (numberOfIterations > 4){
	      		sentence >> xCoorString;
	      		xCoorDouble = atof(xCoorString.c_str());

	      		sentence >> yCoorString;
	      		yCoorDouble = atof(yCoorString.c_str());

	      		sentence >> classNrString;
	      		classNrDouble = atof(classNrString.c_str());

	      		xCoor.push_back(xCoorDouble);
	      		yCoor.push_back(yCoorDouble);
	      		classNr.push_back(classNrDouble);
      		}
      		numberOfIterations++;
    	}
    moonData.close();
  	}else{
  		cout << "Failed to open the file about stock price" << endl;
  	}

  	data.push_back(xCoor);
  	data.push_back(yCoor);
  	data.push_back(classNr);
}


DataIn::~DataIn(){}
