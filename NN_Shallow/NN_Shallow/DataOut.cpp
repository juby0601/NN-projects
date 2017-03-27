#include "DataOut.h"
using namespace std;

DataOut::DataOut(string &input)
{
	vector<int> dateVector;
	vector<int> stockPriceVector;
	string line;
	ifstream stockPriceInfo;
	int yearI, monthI, dayI, yearIPr, monthIPr, dayIPr;
    int stockpriceInt;
    string date,year,month,day;
    string stockprice;

	int numberOfIterations = 1;
	stockPriceInfo.open(input.c_str());
	if (stockPriceInfo.is_open()){
    	while ( getline (stockPriceInfo,line) ){
    		stringstream sentence(line);
      		sentence >> date;

      		stringstream dateSS(date);
      		getline(dateSS,year,'.');
      		getline(dateSS,month,'.');
      		getline(dateSS,day,'.');

      		sentence >> stockprice;

      		//String to int
      		stringstream converterYear(year);
      		converterYear>>yearI;
      		stringstream converterMonth(month);
      		converterMonth>>monthI;
      		stringstream converterDay(day);
      		converterDay>>dayI;

      		stringstream converterStockPrice(stockprice);
      		converterStockPrice>>stockpriceInt;

      		if (numberOfIterations == 1){
      			dateVector.push_back(1);
      		}else{
      			int differenceInDate = numberOfDays(yearI,monthI,dayI) - numberOfDays(yearIPr,monthIPr,dayIPr); 
      			dateVector.push_back(differenceInDate);
      		}
      		stockPriceVector.push_back(stockpriceInt);

      		numberOfIterations++;

      		yearIPr = yearI;
      		monthIPr = monthI;
      		dayIPr = dayI;
    	}
    stockPriceInfo.close();
  	}else if(stockPriceInfo.fail()){
  		cout << "Failed to open the file about stock price" << endl;
  	}

  	data.push_back(dateVector);
  	data.push_back(stockPriceVector);
}

int DataOut::numberOfDays(int year, int month, int day){
	if (month < 3)
		year--, month += 12;
	return 365*year + year/4 - year/100 + year/400 + (153*month - 457)/5 + day - 306;
}


DataOut::~DataOut()
{
	
}
