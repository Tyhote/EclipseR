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
	size_t extraColumns = 0;
	while (checkerSs >> checkerString) {
		try {
			checkerEclipse.InsertNext(checkerString);
		} catch (invalid_argument& e) {
			++extraColumns;
		}
		checkerString = "";
	}
	isPartial = checkerEclipse.GetColumnVal(ECLIPSE_TYPE_COLUMN_INDEX).find('P')
			!= string::npos;

	if (isPartial) {
		if (checkerEclipse.GetCurrColumn() != 16 || extraColumns > 0) {
			cerr << "Error in data row " << row << ": "
					<< checkerEclipse.GetCurrColumn() + extraColumns
					<< " columns found. "
							"Should be 16." << endl;
			return true;
		}
	} else {
		if (checkerEclipse.GetCurrColumn() != 18 || extraColumns > 0) {
			cerr << "Error in data row " << row << ": "
					<< checkerEclipse.GetCurrColumn() + extraColumns
					<< " columns found. "
							"Should be 18." << endl;
			return true;
		}
	}
	return false;
}

ResizableArray<Eclipse> ProcessFile(ifstream& inputFile,
		ResizableArray<Eclipse>& eclipses, size_t attemptedLines, size_t validEclipses) {

	string currentLine;
	string currentDatum;
	int lineNumber = 1; // lineNumber starts at 1 because we skip 10 lines at the beginning
	int columnNumber = 0;

	//  Discard first 10 lines
	for (int i = 0; i < 10; i++) {
		getline(inputFile, currentLine);
	}

	// Getting lines from file while they exist
	while (getline(inputFile, currentLine) && inputFile.good()) {
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
							|| (columnNumber > 3  && columnNumber < 6)
							|| (columnNumber > 6  && columnNumber < 9)
							|| (columnNumber > 13 && columnNumber < 16)
							|| (columnNumber > 15 && !isPartial
									              && columnNumber < 18)) {
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
					if (columnNumber > 9 && columnNumber < 13) {
						stod(currentDatum);

						// Making sure the number was formatted correctly just in case.
						size_t decimalCount = 0;
						for (size_t i = 0; i < currentDatum.size(); ++i) {
							if (currentDatum[i] == '.') {
								++decimalCount;
							}
						}
						if (decimalCount != 1) {
							throw invalid_argument("Not a decimal");
						}

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
			for (int i = 0; i < eclipses.size(); ++i) {

				stringstream outputLine;
				outputLine << currEclipse;
				string catNum = outputLine.str().substr(0,
						outputLine.str().find(',')); //str().substr(0,string::',');

				stringstream auxCompareSS;
				auxCompareSS << eclipses.get(i);
				string compareCatNum = auxCompareSS.str().substr(0,
						auxCompareSS.str().find(','));

				if (catNum.compare(compareCatNum) == 0) {
					isUnique = false;
					cerr << "Error in data row " << lineNumber
							<< ": Duplicate catalog number " << catNum << "."
							<< endl;
					break;
				}
			}
			if (isUnique) {
				eclipses.Add(currEclipse);
			}
		}

		// Resetting variables and incrementing for next line
		++lineNumber;
		columnNumber = 0;
		error = false;
	}
	return eclipses;
}

int main() {
	string userInput;
	bool isDataEntered;
	size_t attemptedLines = 0;
	size_t validEclipses;
	size_t eclipsesInMemory = 0;
	ResizableArray<Eclipse> storedEclipses = ResizableArray<Eclipse>();

	// User inputs file name
	cout << "Enter the name of a file to input." << endl;
	cin >> userInput;
	ifstream inputFile = ifstream();
	while (userInput != "") { // If empty input, exit loop

		inputFile.open(userInput);
		if (!inputFile.fail()) {
			ProcessFile(inputFile, storedEclipses);
			isDataEntered = true;
		} else {
			cout << "File is not available." << endl;
		}

		userInput = "";
		cin >> userInput;
	}

	if (!isDataEntered) { // Exit if no data
		return 0;
	}

	do {
		cout << "Would you like to Output, Sort, Find, or Quit (O,S,F,Q)?"
				<< endl;
		cin >> userInput;
	} while (userInput.compare("O") != 0 && userInput.compare("S") != 0
			&& userInput.compare("F") != 0 && userInput.compare("Q") != 0);

}

