#include "DataOut.h"
using namespace std;

DataOut::DataOut(string &input)
{
	string line;
	ifstream stockPriceInfo;
	stockPriceInfo.open(input.c_str());
	if (stockPriceInfo.is_open()){
    	while ( getline (stockPriceInfo,line) )
    	{
      		cout << line << '\n';
    	}
    stockPriceInfo.close();
  	}else if(stockPriceInfo.fail()){
  		cout << "Failed to open the file about stock price" << endl;
  	}

}


DataOut::~DataOut()
{
	
}
