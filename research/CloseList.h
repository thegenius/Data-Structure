/***************************************************
*  作者：汪蔚                                      *
*  更新：2014-07-15                                *
****************************************************/
#ifndef __CLOSE_LIST_H__
#define __CLOSE_LIST_H__
#include <stdint.h>
#include <algorithm>

class CloseList {
public:
	CloseList(int cap);
	~CloseList();
	void insert(int index, float cost);
	bool isContain(int index);

private:
	float *_value;
	int *_contain;
	int _size;
};

#endif