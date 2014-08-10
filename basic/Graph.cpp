/***************************************************
*  作者：汪蔚                                      *
*  更新：2014-07-13                                *
****************************************************/

#include "Graph.h"
#include <stdio.h>

GraphArc::GraphArc(uint64_t dest, uint64_t cost, void*data, GraphArc*next) :
	dest(dest), cost(cost), data(data), next(next) {
}

GraphNode::GraphNode() : info((void*)nullptr), first_arc(nullptr) {
}

Graph::Graph(uint64_t size) {
	if (size <= 0) {
		this->size = 0;
		node = nullptr;
	} else {
		this->size = size;
		node = new GraphNode[size];
	}
}

Graph::Graph(uint64_t sizeI, uint64_t sizeJ) {
	this->sizeI = sizeI;
	this->sizeJ = sizeJ;
	this->size = sizeI * sizeJ;
	if (size <= 0) {
		this->size = 0;
		node = nullptr;
	} else {
		this->size = size;
		node = new GraphNode[size];
	}
}

// 请特别注意链表的清理工作
Graph::~Graph() {
	for (int i=0; i<size; ++i) {	
		while (node[i].first_arc != nullptr) {
			auto x = node[i].first_arc;
			node[i].first_arc = x->next;
			delete x;
		}
	}
	if (node != nullptr) {
		delete[] node;
	}
}

// 假设不会插入重复边
bool Graph::insertArc(uint64_t from, uint64_t to, float cost) {
	GraphArc* arc = new GraphArc(to);
	arc->next = this->node[from].first_arc;
	this->node[from].first_arc = arc;
	this->node[from].first_arc->cost = cost;
	return true;
}

float Graph::getCost(uint64_t from, uint64_t to) {
	for (auto arc=node[from].first_arc; arc!=nullptr; arc=arc->next) {
		if (arc->dest == to) {
			return arc->cost;
		}
	}
}

void Graph::print() {
	printf("\n");
	for (int i=0; i<size; ++i) {
		printf("node[%d]: ", i);
		for (auto arc=node[i].first_arc; arc!=nullptr; arc=arc->next) {
			printf("%d[%d] ", arc->dest, arc->cost);
		}
		printf("\n");
	}
}
