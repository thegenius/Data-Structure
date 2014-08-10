/****************************************************
* ͼ���ڽӱ�ʵ�� 
* ���ߣ� ��ε
* ���£� 2014-07-13                                 
*****************************************************/

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdint.h>


struct GraphArc {
public:
    GraphArc(uint64_t dest, uint64_t cost=0, void*data=nullptr, GraphArc*next=nullptr);
public:
    uint64_t dest;
    float    cost;
    void*    data;
    GraphArc* next;  
};

struct GraphNode {
public:
    GraphNode();
public:
    union info_union {
        info_union(uint8_t ch) : ch(ch) {}
        info_union(char* str)  : str(str) {}
        info_union(void* data) : data(data) {}
        uint8_t ch;
        char* str;
        void* data;
    }info;
    GraphArc* first_arc;
};


struct Graph {
public:
    Graph(uint64_t size);
	Graph(uint64_t sizeI, uint64_t sizeJ);
	~Graph();
    bool insertArc(uint64_t from, uint64_t to, float cost=1.0f);
	float getCost(uint64_t from, uint64_t to);
	void print();
public:
    uint64_t size;
	uint64_t sizeI;  //Ϊ��άƽ���趨, ��ά��߱任��1ά��������ʱ����Ҫ֪����Ⱥ͸߶�
	uint64_t sizeJ;  //Ϊ��άƽ���趨
    GraphNode*  node;
};


#endif                                                                                                                                                                                             1,1           All
