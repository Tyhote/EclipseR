/*
 * Eclipse.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: tdow
 */
#include "Eclipse.h"

int currColumn = 0;

Eclipse::Eclipse() {
	ResizableArray<string> array = ResizableArray<string>();
	currColumn = 0;
}

Eclipse::~Eclipse() {
}

Eclipse& Eclipse::operator=(const Eclipse &eclipse) {
	currColumn = 0;
	for (int i = 0; i < eclipse.currColumn; ++i) {
		InsertNext(eclipse.columnArray[i]);
	}
	return *this;
}

void Eclipse::InsertNext(string value) {
	if(currColumn < NUM_COLUMNS){
	columnArray[currColumn] = value;
	currColumn++;
	} else {
		throw invalid_argument("Too many columns entered.");
	}
}

std::ostream& operator<<(std::ostream &out, const Eclipse& eclipse) {
	for (int i = 0; i < eclipse.currColumn - 1; ++i) {
		out << eclipse.columnArray[i] << ",";
	}
	out << eclipse.columnArray[eclipse.currColumn - 1];
	return out;
}

