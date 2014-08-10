/***************************************************
*  作者：汪蔚                                      *
*  更新：2014-07-13                                *
****************************************************/
#ifndef __QUEUE_H
#define __QUEUE_H
#include <stdio.h>
#include <stdint.h>

struct Queue {
public:
    Queue(uint64_t capacity);
	virtual ~Queue();

	void enqueue(uint64_t x);
    bool dequeue(uint64_t& x);

    bool isEmpty();
    bool isFull();
    uint64_t size();

    void print();
public:
    uint64_t front;
    uint64_t back;
    uint64_t capacity;
    uint64_t *q;
};



#endif