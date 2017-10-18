/*
 * ArrayList.h
 *
 *  Created on: Sep 12, 2017
 *      Author: tdow
 */

#ifndef RESIZABLEARRAY_H_
#define RESIZABLEARRAY_H_
#define ARRAYLIST_CPP
#include <iostream>
template<class T>
class ResizableArray {
public:
	friend std::ostream& operator<<(std::ostream &out, const ResizableArray& AList) {
		for (int i = AList.size() -1; i >= 0 ; --i) {
			out << AList.get(i) << std::endl;
		}
		return out;
	}
	ResizableArray<T>(unsigned int size);
	ResizableArray<T>();
	~ResizableArray<T>();
	void* operator new(size_t size);
	void Add(T object);
	void AddAt(T object, unsigned int i);
	void Remove(T object);
	void RemoveAt(unsigned int i);
	T get(unsigned int i) const;
	void set(unsigned int i, T value);
	int size() const{
		return numItems;
	}
	int arraySize() {
		return arrSize;
	}
private:
	void increase();
	void decrease();
	unsigned int arrSize;
	unsigned int numItems = 0;
	T* array;
};

template<class T>
ResizableArray<T>::ResizableArray() {
	arrSize = 10;
	T* temp = new T[arrSize];
	array = temp;
}

template<class T>
ResizableArray<T>::ResizableArray(unsigned int size) {
	arrSize = size;
	T* temp = new T[arrSize];
	array = temp;
}
template<class T>
void* ResizableArray<T>::operator new(size_t size) {
	ResizableArray<T>* aux = ::new ResizableArray<T>();
	aux->arrSize = size;
	aux->array = new T[size];
	return aux;
}

template<class T>
ResizableArray<T>::~ResizableArray() {
	delete[] array;
}

template<class T>
void ResizableArray<T>::Add(T object) {
	if (numItems >= arrSize) {
		increase();
	}
	array[numItems] = object;
	numItems++;
}

template<class T>
void ResizableArray<T>::AddAt(T object, unsigned int index) {
	if (numItems >= arrSize) {
		increase();
	}
	if (index > numItems) {
		throw "Index out of bounds.";
	}
	if(index == numItems){
		Add(object);
		return;
	}

	T* aux = new T[numItems + 1];
	for (int i = 0; i < index; ++i) {
		aux[i] = array[i];
	}
	aux[index] = object;
	for (int i = index + 1; i < numItems; ++i) {
		aux[i] = array[i - 1];
	}
	delete[] array;
	array = aux;
	numItems++;
}

template<class T>
void ResizableArray<T>::Remove(T object) {
	if (numItems <= arrSize / 2) {
		decrease();
	}
	for (int i = 0; i < numItems; i++) {
		if (array[i] == object) {
			T* aux = new T[arrSize - 1];
			for (int j = 0; j < i; ++j) {
				aux[j] == array[j];
			}
			for (int j = i + 1; j < arrSize - 1; ++j) {
				aux[j] = array[j];
			}
			delete[] array;
			array = aux;
			return;
		}
	}
	throw "Item not found";
}

template<class T>
void ResizableArray<T>::RemoveAt(unsigned int index) {
	if (numItems <= arrSize / 2) {
		decrease();
	}
	if (index >= numItems) {
		throw "Index out of bounds";
	}

	T* aux = new T[arrSize - 1];
	for (int i = 0; i < index; ++i) {
		aux[i] == array[i];
	}
	for (int i = index + 1; i < arrSize - 1; ++i) {
		aux[i] = array[i];
	}
	delete array;
	array = aux;
	return;
}

template<class T>
T ResizableArray<T>::get(unsigned int i) const{
	if (i < numItems) {
		return array[i];
	}
	throw std::invalid_argument("Index out of range");
}

template<class T>
void ResizableArray<T>::set(unsigned int i, T value) {
	if (i < numItems) {
		array[i] = value;
	}
	throw std::invalid_argument("Index out of range");
}

template<class T>
void ResizableArray<T>::increase() {
	T* aux = new T[arrSize * 2];
	for (unsigned int i = 0; i < arrSize; i++) {
		aux[i] = array[i];
	}
	delete[] array;
	arrSize *= 2;
	array = aux;
}

template<class T>
void ResizableArray<T>::decrease() {
	T* aux = new T[arrSize / 2];
	for (int i = 0; i < numItems; i++) {
		aux[i] = array[i];
	}
	delete[] array;
	arrSize /= 2;
	array = aux;
}

#endif /* RESIZABLEARRAY_H_ */
