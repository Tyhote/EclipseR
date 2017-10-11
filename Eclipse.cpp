/*
 * Eclipse.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: tdow
 */
#include "Eclipse.h"

int currColumn = 0;

Eclipse::Eclipse(){
	currColumn = 0;
}

Eclipse::~Eclipse(){
}

Eclipse& Eclipse::operator=(const Eclipse &eclipse){
	for(int i = 0; i < NUM_COLUMNS; i++){
		array[i] = "";
	}
	currColumn = 0;
	for(int i = 0; i < eclipse.currColumn; ++i){
		InsertNext(eclipse.array[i]);
	}
	return *this;
}

void Eclipse::InsertNext(string value){
	if(currColumn < 18){
		array[currColumn] = value;
		currColumn++;
	} else {
		throw "Inserted too much data into individual Eclipse.";
	}
}

std::ostream& operator<<(std::ostream &out, const Eclipse& eclipse) {
	for (int i = 0; i < eclipse.currColumn - 1; ++i) {
		out << eclipse.array[i] << ", ";
	}
	out << eclipse.array[currColumn];
	return out;
}

