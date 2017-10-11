/*
 * EclipseR.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: Tristan Dow
 */

#include "EclipseR.h"
using namespace std;

bool hasWrongColumns(string currentLine, int row, bool& isPartial) {
	stringstream checkerSs(currentLine);
	string checkerString = "";
	Eclipse checkerEclipse;
	while (checkerSs >> checkerString) {
		checkerEclipse.InsertNext(checkerString);
		checkerString = "";
	}
	isPartial = checkerEclipse.GetColumnVal(ECLIPSE_TYPE_COLUMN_INDEX).find('P') != string::npos;

	if (isPartial) {
		if (checkerEclipse.GetCurrColumn() != 16) {
			cerr << "Error in data row " << row << ": " << checkerEclipse.GetCurrColumn()
					<< " columns found. "
							"Should be 16." << endl;
			return true;
		}
	} else {
		if (checkerEclipse.GetCurrColumn() != 18) {
			cerr << "Error in data row " << row << ": " << checkerEclipse.GetCurrColumn()
					<< " columns found. "
							"Should be 18." << endl;
			return true;
		}
	}
	return false;
}

int main() {

	string currentLine;
	string currentDatum;
	int lineNumber = 11; // lineNumber starts at 11 because we skip 10 lines at the beginning
	int columnNumber = 0;
	ResizableArray<Eclipse> processedData = ResizableArray<Eclipse>();

	//  Discard first 10 lines
	for (int i = 0; i < 10; i++) {
		getline(cin, currentLine);
	}

	// Getting lines from file while they exist
	while (getline(cin, currentLine) && cin.good()) {
		// Iterating through each column
		stringstream ss(currentLine);
		Eclipse currEclipse = Eclipse();
		bool isPartial;
		bool error;
		// This tells whether there is an error in the number of columns, but also sets isPartial appropriately.
		error = hasWrongColumns(currentLine, lineNumber, isPartial);

		if (!error) {
			while (ss >> currentDatum) {

				// Data type error checking
				try {
					if ((columnNumber > 0 && columnNumber < 3)
							|| (columnNumber > 3 && columnNumber < 6)
							|| (columnNumber > 6 && columnNumber < 9)
							|| (columnNumber > 13 && columnNumber < 16)
							|| (columnNumber > 15 && !isPartial && columnNumber < 18)) {
						stol(currentDatum);
					}
				} catch (invalid_argument& e) {
					error = true;
					cerr << "Error in data row " << lineNumber << ": "
							"Column " << columnNumber + 1
							<< " is not a whole number." << endl;
					++columnNumber;
					continue;
				}
				try {
					if (columnNumber > 10 && columnNumber < 13) {
						stod(currentDatum);
					}
				} catch (invalid_argument& e) {
					error = true;
					cerr << "Error in data row " << lineNumber << ": "
							"Column " << columnNumber + 1
							<< " is not a decimal number." << endl;
					++columnNumber;
					continue;
				}

				// If eclipse is partial, no need for two extra columns
				if (isPartial) {
					if (columnNumber == PARTIAL_COLUMN_COUNT) {
						currEclipse.InsertNext(currentDatum);
						++columnNumber;
						continue;
					}
				} else if (columnNumber == NON_PARTIAL_COLUMN_COUNT) {
					currEclipse.InsertNext(currentDatum);
					++columnNumber;
					continue;
				}
				currEclipse.InsertNext(currentDatum);

				// If this column succeeds, increment column number
				++columnNumber;
			}
		}

		// Checking for duplicates if no error in row
		if (!error) {
			bool isUnique = true;
			for (int i = 0; i < processedData.size(); ++i) {

				stringstream outputLine;
				outputLine << currEclipse;
				string catNum = outputLine.str().substr(0,outputLine.str().find(',')); //str().substr(0,string::',');

				stringstream auxCompareSS;
				auxCompareSS << processedData.get(i);
				string compareCatNum = auxCompareSS.str().substr(0, auxCompareSS.str().find(','));

				if (catNum.compare(compareCatNum) == 0) {
					isUnique = false;
					cerr << "Error in row " << lineNumber << ": Duplicate catalog number " << catNum << "." << endl;
					break;
				}
			}
			if (isUnique) {
				processedData.Add(currEclipse);
			}
		}

		// Resetting variables and incrementing for next line
		++lineNumber;
		columnNumber = 0;
		error = false;
	}
	cout << processedData;
}

