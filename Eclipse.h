/*
 * Eclipse.h
 *
 *  Created on: Sep 28, 2017
 *      Author: tdow
 */

#ifndef ECLIPSE_H_
#define ECLIPSE_H_
#include "EclipseR.h"
#include "ResizableArray.h"
const int NUM_COLUMNS = 18;
using namespace std;
class Eclipse {
public:
	Eclipse();
	~Eclipse();
	int GetCurrColumn() {
		return currColumn;
	}
	string GetColumnVal(int i ){
		if(i < currColumn){
		return columnArray[i];
		}
		throw "Index out of bounds";
	}
	void InsertNext(string value);
	Eclipse& operator=(const Eclipse &eclipse);
private:
	friend std::ostream& operator<<(std::ostream &out, const Eclipse& eclipse);
	string columnArray[NUM_COLUMNS];
	int currColumn;
};

#endif /* ECLIPSE_H_ */
