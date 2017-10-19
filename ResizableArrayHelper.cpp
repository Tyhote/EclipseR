/*
 * ResizableArrayHelper.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: tdow
 */
#include "ResizableArrayHelper.h"
ResizableArray<Eclipse> Sort(const ResizableArray<Eclipse>& eclipses, size_t columnNumber) {
	return MergeSort(eclipses, columnNumber);
}

ResizableArray<Eclipse> MergeSort(const ResizableArray<Eclipse>& eclipses,
		size_t columnNumber) {
	if (eclipses.size() <= 1) {
		return eclipses;
	}

	ResizableArray<Eclipse> left = ResizableArray<Eclipse>();
	ResizableArray<Eclipse> right = ResizableArray<Eclipse>();
	for (int i = 0; i < eclipses.size() / 2; ++i) {
		left.Add(eclipses.get(i));
	}

	for (int i = eclipses.size() / 2; i < eclipses.size(); i++) {
		right.Add(eclipses.get(i));
	}

	left = MergeSort(left, columnNumber);
	right = MergeSort(right, columnNumber);

	return Merge(left, right, columnNumber);
}

ResizableArray<Eclipse> Merge(const ResizableArray<Eclipse>& left,
		const ResizableArray<Eclipse>& right, size_t columnNumber) {
	ResizableArray<Eclipse> mergedArray = ResizableArray<Eclipse>();
	int i = 0;
	int j = 0;
	if (columnNumber == 1) {
		while (i < left.size() && j < right.size()) {
			if (left.get(i).GetColumnVal(columnNumber)
					<= right.get(j).GetColumnVal(columnNumber)) {
				mergedArray.Add(left.get(i));
				i++;
			} else {
				mergedArray.Add(right.get(j));
				j++;
			}
		}
	} else {
		while (i < left.size() && j < right.size()) {
			if (left.get(i).GetColumnVal(columnNumber).compare(
					right.get(j).GetColumnVal(columnNumber)) <= 0) {
				mergedArray.Add(left.get(i));
				i++;
			} else {
				mergedArray.Add(right.get(j));
				j++;
			}
		}
	}

	while (i < left.size()) {
		mergedArray.Add(left.get(i));
		i++;
	}
	while (j < right.size()) {
		mergedArray.Add(right.get(i));
	}

	return mergedArray;
}



ResizableArray<Eclipse> BinarySearch(const ResizableArray<Eclipse>& eclipses,
		string key, size_t column) {
	ResizableArray<Eclipse> result = ResizableArray<Eclipse>();
	size_t min = 0;
	size_t max = eclipses.size() - 1;
	if (max <= 0) {
		return -1;
	}

	size_t mid = (max + min) / 2;
	if (column == 1) {
		int keyVal = stoi(key);
		int catVal = stoi(eclipses.get(mid).GetColumnVal(column));
		while (catVal != keyVal) {
			if (catVal < keyVal) {
				min = mid + 1;
			}
			if (catVal > keyVal) {
				max = min - 1;
			}
			mid = (max + min) / 2;
			catVal = stoi(eclipses.get(mid).GetColumnVal(column));
		}
		result.Add(eclipses.get(mid));
	} else {
		string catVal = eclipses.get(mid).GetColumnVal(column);
		while (catVal.compare(key) != 0) {
			if (catVal.compare(key) < 0) {
				min = mid + 1;
			}
			if (catVal.compare(key) > 0) {
				max = min - 1;
			}
		}
		int left = mid;
		while (left > 0
				&& eclipses.get(left - 1).GetColumnVal(column).compare(key) == 0) {
			left--;
		}

		int right = mid + 1;
		while (right < eclipses.size() && eclipses.get(right).GetColumnVal(column).compare(key) == 0) {
				right++;
		}
		for(int i = left; i < right; ++i){
			result.Add(eclipses.get(i));
		}
	}
	return result;
}

ResizableArray<Eclipse> LinearSearch(ResizableArray<Eclipse>& eclipses,
		string key, size_t column) {
	ResizableArray<Eclipse> result = ResizableArray<Eclipse>();
	if (column == 1) {
		int keyVal = stoi(key);
		for (int i = 0; i < eclipses.size(); ++i) {
			Eclipse eclipse = eclipses.get(i);
			if (stoi(eclipse.GetColumnVal(column)) == keyVal) {
				result.Add(eclipse);
			}
			break;
		}
	} else {
		for (int i = 0; i < eclipses.size(); ++i) {
			Eclipse eclipse = eclipses.get(i);
			if (eclipse.GetColumnVal(column).compare(key) == 0) {
				result.Add(eclipse);
			}
		}
	}
	return result;
}
