/*
 * ResizableArrayHelper.h
 *
 *  Created on: Oct 18, 2017
 *      Author: tdow
 */

#ifndef RESIZABLEARRAYHELPER_H_
#define RESIZABLEARRAYHELPER_H_
#include "Eclipse.h"
ResizableArray<Eclipse> Sort(const ResizableArray<Eclipse>& eclipses, size_t columnNumber);
ResizableArray<Eclipse> MergeSort(const ResizableArray<Eclipse>& eclipses, size_t columnNumber);
ResizableArray<Eclipse> Merge(const ResizableArray<Eclipse>& left, const ResizableArray<Eclipse>& right, size_t columnNumber);
ResizableArray<Eclipse> BinarySearch(const ResizableArray<Eclipse>& eclipses, string key, size_t columnNumber);
ResizableArray<Eclipse> LinearSearch(const ResizableArray<Eclipse>& eclipses, string key, size_t column);



#endif /* RESIZABLEARRAYHELPER_H_ */
