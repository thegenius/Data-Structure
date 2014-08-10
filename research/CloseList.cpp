/***************************************************
*  作者：汪蔚                                      *
*  更新：2014-07-15                                *
****************************************************/

#include "CloseList.h"

CloseList::CloseList(int cap) : 
	_size(0), 
	_value(new float[cap]), 
	_contain(new int[cap]) {
	for (int i=0; i<cap; ++i) {
		_value[i] = 1E7;
		_contain[i] = 0;
	}
}
CloseList::~CloseList() {
	if (_value != nullptr) {
		delete[] _value;
	}
	if (_contain != nullptr) {
		delete[] _contain;
	}
}

void CloseList::insert(int index, float cost) {
	_value[index] = cost;
	_contain[index] = 1;
}

bool CloseList::isContain(int index) {
	return _contain[index] != 0;
}
