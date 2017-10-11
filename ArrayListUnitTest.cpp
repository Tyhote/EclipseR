/*
 * ArrayListUnitTest.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: tdow
 */
#include <iostream>

#include "ResizableArray.h"
using namespace std;
int test() {
	cout << "Testing overloaded constructor." << endl;
	ResizableArray<string> constructorList = ResizableArray<string>();
	cout << "ArrayList size is " << constructorList.size() << "." << endl;
	cout << "Array size is " << constructorList.arraySize() << endl;
	for (int i = 0; i < 2000; i++) {
		constructorList.Add(to_string(i));
	}
	cout << "ArrayList size is " << constructorList.size() << "." << endl;
	for (int i = 0; i < constructorList.size(); i++) {
		cout << constructorList.get(i) << endl;
	}

	cout << "Testing overloaded contructor with params." << endl;
	ResizableArray<string> newList = ResizableArray<string>(20);
	cout << "ArrayList size is " << newList.size() << "." << endl;
	for (int i = 0; i < newList.arraySize(); i++) {
		newList.Add(to_string(i));
	}
	cout << "ArrayList size is " << newList.size() << "." << endl;
	cout << "Array size is " << newList.arraySize() << endl;
	for (int i = 0; i < newList.size(); i++) {
		cout << newList.get(i) << endl;
	}
	return 0;
}

