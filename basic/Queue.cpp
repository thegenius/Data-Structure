/***************************************************
*  作者：汪蔚                                      *
*  更新：2014-07-13                                *
****************************************************/
#include "Queue.h"

// 辅助函数
// 取得最接近且不小于当前值x的2的方幂
static uint64_t next_power2(uint64_t x) {
    -- x;
    x = x | x>>1;
    x = x | x>>2;
    x = x | x>>4;
    x = x | x>>8;
    x = x | x>>16;
    x = x | x>>32;
    ++ x;
    return x;
}

/************************************
*      构造和析构函数               *
*************************************/
Queue::Queue(uint64_t capacity) {
	front = 0;
	back  = 0;
	this->capacity = next_power2(capacity+1);
	q = new uint64_t[this->capacity];
}

Queue::~Queue() {
	if (q != nullptr) {
		delete q;
	}
}

/************************************
*      插入和删除操作               *
*************************************/
void Queue::enqueue(uint64_t x) {
	if (isFull()) {
		uint64_t *newq = new uint64_t[capacity<<1];
		uint64_t newback = 0;
		for (int i=front; i!=back; i=++i&(capacity-1)) {
			newq[newback++] = q[i];
		}
		delete []q;
		q = newq;
		front = 0;
		back = newback;
		capacity = capacity<<1;
	}

	q[back] = x;
	back = ++back & (capacity-1);
}

bool Queue::dequeue(uint64_t& x) {
	if (isEmpty()) {
		return false;
	}
	x = q[front];
	front = ++front & (capacity-1);
	return true;
}


/************************************
*      容量相关函数                 *
*************************************/
bool Queue::isEmpty() {
	return front==back;
}

bool Queue::isFull() {
	return front-back==1 || back-front==capacity-1;
}

uint64_t Queue::size() {
	int size = back-front;
	if (size < 0) {
		size += capacity;
	}
	return size;
}

/************************************
*      调试打印函数                 *
*************************************/
void Queue::print() {
	for (int i=front; i!=back; i=++i&(capacity-1)) {
		printf("%c\t", q[i]+'A');
	}
	printf("\n");
}

