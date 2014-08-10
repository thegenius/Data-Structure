/***************************************************
*  ���ߣ���ε                                      *
*  ���£�2014-07-17                                *
****************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "TreeArray.h"
#include "TileMap.h"
#include "Queue.h"
#include "Graph.h"
#include "OpenList.h"
#include "CloseList.h"
#include "Geometry.h"
#include "Graph.h"
USING_NS_CC;

struct Path {
	Path (int *arr, int size) {
		came_from = new int[size];
		this->size = size;
		for (int i=0; i<size; ++i) {
			came_from[i] = arr[i];
		}
	}
	~Path() {
		if (came_from != nullptr) {
			delete[] came_from;
		}
	}
	int *came_from;
	int size;
};

class AStarHelper {
public:
	AStarHelper(int node_size) {
		_openSet  = new OpenList(node_size);
		_closeSet = new CloseList(node_size);
		g_score   = new float[node_size];
		f_score   = new float[node_size];
		cost      = new float[node_size];
		path      = new int[node_size];
		memset(g_score,      0x7f, sizeof(int)*node_size);  
		memset(f_score,      0x7f, sizeof(int)*node_size);  
		memset(path,         0xff, sizeof(int)*node_size);  //0xffffffff == -1
		for (int i=0; i<node_size; ++i) {
			cost[i] = 1E7;
		}
		nodeSize = node_size;
	}
	~AStarHelper() {
		if (_openSet != nullptr) {
			delete _openSet; 
		};
		if (_closeSet != nullptr) {
			delete _closeSet;
		}
		if (g_score != nullptr) {
			delete[] g_score;
		}
		if (f_score != nullptr) {
			delete[] f_score;
		}
		if (cost != nullptr) {
			delete[] cost;      
		}
		if (path != nullptr) {
			delete[] path;   
		}
	}
	void insertPath(int src, int dst, int cst=1) {
		path[dst] = src;
		cost[dst] = cst;
	}
	void printPath(int dst) {
		if (path[dst] != -1) {
			printPath(path[dst]);
			printf(" --[%f]--> %d", cost[dst], dst);
		} else {
			printf("%d", dst);
		}
	}
	Path * getPath(int dst) {
		return new Path(path, nodeSize);
	}
public:
	int nodeSize;
	OpenList  *_openSet;
	CloseList *_closeSet;

	int *path;         // ��¼·�������飬ÿ����Ԫ������ָ��·����ǰһ���ڵ���±�
	float *cost;         // ��¼·���Ĵ���
	float *g_score;      // �ӿ�ʼ�ڵ㣬��Ŀǰ�ڵ�����·����cost
	float *f_score;      // �ӿ�ʼ�ڵ㣬��Ŀ��ڵ��cost�Ĺ���
};

float heuristic_cost_estimate(Graph &g, int src, int dst) {
	Vec2 pos1(src/g.sizeJ, src%g.sizeJ);
	Vec2 pos2(dst/g.sizeJ, dst%g.sizeJ);
	return ccpDistance(pos1, pos2);
	//return 0.0f;
}

Path* AStarTraverse(Graph& g, int src, int dst) {

	AStarHelper helper(g.size);

	// ��ʼ��open��close��Ϊ�ղ���Ҫ������ʽ��ʼ��
	helper._openSet->insert(src, 0.0f);
	helper.g_score[src] = 0;
	helper.f_score[src] = helper.g_score[src] + heuristic_cost_estimate(g, src, dst);

	while (!helper._openSet->isEmpty()) {

		// ��open������ȡf(x)��С�Ľڵ�
		int curr = -1;
		float cost = 0;
		helper._openSet->extractMin(curr, cost);
		helper._closeSet->insert(curr, cost);

		// ����Ѿ��ҵ�
		if (curr == dst) {
			break;
		}

		// �����û���ҵ�Ŀ��ڵ㣬�����������ڽڵ�
		for (GraphArc *arc=g.node[curr].first_arc; arc!=NULL; arc=arc->next) {

			int neighbour = arc->dest;
			// ���������ڽڵ��Ѿ���close��
			if (helper._closeSet->isContain(neighbour)) {
				continue;
			}
			// ���������ǰ�ڵ㣬�������ڽڵ���ӽ�ʡ����
			float tentative_g_score = helper.g_score[curr] + arc->cost;
			if (tentative_g_score < helper.g_score[neighbour]) {
				helper.g_score[neighbour] = tentative_g_score;
				helper.insertPath(curr, neighbour, arc->cost);
			}
			// ���¼���������ڽڵ��f(x)ֵ
			float tentative_f_score = helper.g_score[neighbour] + heuristic_cost_estimate(g, neighbour, dst);
			if (tentative_f_score < helper.f_score[neighbour]) {
				helper.f_score[neighbour] = tentative_f_score;
			}
			// �����ӵ�open����
			helper._openSet->insert(neighbour, helper.f_score[neighbour]);
		}
	}

	return helper.getPath(dst);
}

/******************************************************************
*   ����任��غ���
*
*******************************************************************/
ScreenCoord TileMap::getScreenCoord(TileCoord tileCoord) {
	// �������Ӧ�������½ǵĵ�
	float x = tileCoord.j * (1.0/GRID_SCALE);
	float y = tileCoord.i * (1.0/GRID_SCALE);
	ScreenCoord screenCoord(x, y);

	//���½ǵ㵽���ĵ�ƫ��
	Vec2 offset(1.0/GRID_SCALE*0.5, 1.0/GRID_SCALE*0.5);
	screenCoord = screenCoord + offset;
	return screenCoord;
}

ScreenCoord TileMap::getScreenCoord(GraphCoord graphCoord) {
	auto tileCoord = getTileCoord(graphCoord);
	return getScreenCoord(tileCoord);
}

GraphCoord TileMap::getGraphCoord(TileCoord tileCoord) {
	return tileCoord.i*tileJ + tileCoord.j;
}

GraphCoord TileMap::getGraphCoord(ScreenCoord screenCoord) {
	auto tileCoord = getTileCoord(screenCoord);
	return getGraphCoord(tileCoord);
}

TileCoord TileMap::getTileCoord(GraphCoord graphCoord) {
	int i = graphCoord/tileJ;
	int j = graphCoord%tileJ;
	return TileCoord(i,j);
}

TileCoord TileMap::getTileCoord(ScreenCoord screenCoord) {
	int i = (int)(screenCoord.y * GRID_SCALE);
	int j = (int)(screenCoord.x * GRID_SCALE);
	return TileCoord(i,j);
}




// �����������繹����һ��tile map
bool TileMap::makeTileMapFromPhysics() {
	for (int i=0; i<tileI; ++i) {
		for (int j=0; j<tileJ; ++j) {
			TileCoord tileCoord(i, j);
			Vec2 center = getScreenCoord(tileCoord);
			// ��ѯ������ӽڵ��Ƿ񱻸���
			bool isOverlap = false;
			auto neighbours = GCPhysicsWorld::getInstance()->getNeighbour(center, 1.0/GRID_SCALE*0.5);
			if (neighbours != nullptr) {
				isOverlap = true;
			} 
			// ����tile����
			if (isOverlap) {
				matrix[i][j] = 1E7; //����Ϊ���ɵ���
			} else {
				matrix[i][j] = 1.0f;
			}
		}
	}
	return true;
}

// ����tile��������
void TileMap::drawAsterByTile() {

	this->drawAsterNode->clear();

	for (int i=0; i<tileI; ++i) {
		for (int j=0; j<tileJ; ++j) {
			if (matrix[i][j] > 1E6) {

				TileCoord tileCoord(i, j);
				Vec2 center = getScreenCoord(tileCoord);
				Vec2 offset1(1.0/GRID_SCALE*0.5,  1.0/GRID_SCALE*0.5);
				Vec2 offset2(-1.0/GRID_SCALE*0.5, 1.0/GRID_SCALE*0.5);
				Point rectangle[4];
				rectangle[0] = Point(center-offset1);
				rectangle[1] = Point(center-offset2);
				rectangle[2] = Point(center+offset1);
				rectangle[3] = Point(center+offset2);

				this->drawAsterNode->drawPolygon(rectangle, 4, Color4F::RED, 1.0f, Color4F::RED);
			}
		}
	}
}

void TileMap::drawAsterByGraph() {
	static Queue vq(tileI*tileJ);
	while (!vq.isEmpty()) {
		uint64_t x;
		vq.dequeue(x);
	}


	this->drawAsterNode->clear();
	Graph *g = getGraph();

	// ������ȱ���
	// �߽���
	if (g->size <= 0) {
		return;
	}
	// ��ʼ�����ʱ�ʶ����
	uint64_t *visit = new uint64_t[g->size];
	memset(visit, 0, g->size*sizeof(uint64_t));
	// ��ʼ�ڵ���ջ

	vq.enqueue(100);
	++visit[100];
	// ��ʼ������ȱ���
	while (!vq.isEmpty()) {
		uint64_t vindex;
		vq.dequeue(vindex);
		// ���ʶ���
		//printf("visit %d\n", vindex);

		// ��չ
		for (auto *arc=g->node[vindex].first_arc; arc!=NULL; arc=arc->next) {
			if (visit[arc->dest] == 0) {
				vq.enqueue(arc->dest);
				++visit[arc->dest];


				Vec2 center = getScreenCoord(arc->dest);
				Vec2 offset1(1.0/GRID_SCALE*0.5,  1.0/GRID_SCALE*0.5);
				Vec2 offset2(-1.0/GRID_SCALE*0.5, 1.0/GRID_SCALE*0.5);
				Point rectangle[4];
				rectangle[0] = Point(center-offset1);
				rectangle[1] = Point(center-offset2);
				rectangle[2] = Point(center+offset1);
				rectangle[3] = Point(center+offset2);
				this->drawAsterNode->drawPolygon(rectangle, 4, Color4F::GREEN, 1.0f, Color4F::GREEN);

			}
		}
	}
	delete visit;
	delete g;
	return;
}

void TileMap::drawGrid() {
	for (int i=0; i<tileI; ++i) {
		for (int j=0; j<tileJ; ++j) {
			// �����ĸ�����
			TileCoord tileCoord(i, j);
			Vec2 center = getScreenCoord(tileCoord);
			Vec2 offset1(1.0/GRID_SCALE*0.5,  1.0/GRID_SCALE*0.5);
			Vec2 offset2(-1.0/GRID_SCALE*0.5, 1.0/GRID_SCALE*0.5);
			Point rectangle[4];
			rectangle[0] = Point(center-offset1);
			rectangle[1] = Point(center-offset2);
			rectangle[2] = Point(center+offset1);
			rectangle[3] = Point(center+offset2);

			this->drawGridNode->drawSegment(rectangle[0], rectangle[1], 0.5f, Color4F::RED);
			this->drawGridNode->drawSegment(rectangle[1], rectangle[2], 0.5f, Color4F::RED);
			this->drawGridNode->drawSegment(rectangle[2], rectangle[3], 0.5f, Color4F::RED);
			this->drawGridNode->drawSegment(rectangle[3], rectangle[0], 0.5f, Color4F::RED);
		}
	}
}

void TileMap::drawPath(Vec2 src, Vec2 dst) {
	Graph *g = getGraph();
	// ����Ļλ��ת��Ϊ�ڲ�Graph����
	auto pos1 = getGraphCoord(src);
	auto pos2 = getGraphCoord(dst);
	auto path = AStarTraverse(*g, pos1, pos2);

	int from = path->came_from[pos2];
	while (from != -1) {
		auto screenPos = getScreenCoord(from);
		this->drawPathNode->drawDot(screenPos, 3.0f, Color4F::BLUE);
		from = path->came_from[from];
	}

	this->drawPathNode->drawDot(getScreenCoord(pos1), 3.0f, Color4F::YELLOW);
	this->drawPathNode->drawDot(getScreenCoord(pos2), 3.0f, Color4F::YELLOW);
	delete g;
}

TileMap* TileMap::create(float width, float height) {
	TileMap *pRet = new TileMap(width, height); 
	if (pRet && pRet->init()) { 
		pRet->autorelease(); 
		return pRet; 
	} 
	else { 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}

TileMap::TileMap(float width, float height) {
	contentWidth = width;
	contentHeight = height;
	auto tileCoord = getTileCoord(ScreenCoord(width, height));
	tileI = tileCoord.i;
	tileJ = tileCoord.j;
	matrix = new float*[tileI];
	for (int i=0; i<tileI; ++i) {
		matrix[i] = new float[tileJ];
	}

	//��ʼ������tile���ͨ������Ϊ1.0f,��ʾ����ͨ��
	for (int i=0; i<tileI; ++i) {
		for (int j=0; j<tileJ; ++j) {
			matrix[i][j] = 1.0f;
		}
	}
}
bool TileMap::init() {

	//*/ ���Ʋ���
	drawGridNode = DrawNode::create();
	drawAsterNode = DrawNode::create();
	drawPathNode = DrawNode::create();
	addChild(drawGridNode);
	addChild(drawAsterNode);
	addChild(drawPathNode);

	drawGrid();
	makeTileMapFromPhysics();

	//*/

	scheduleUpdate();
	return true;
}

void TileMap::update(float dt) {
	static int updatePath = 1;

	makeTileMapFromPhysics();
	drawAsterByTile();
	updatePath --;
	if (updatePath < 0) {
		updatePath = 1;
		drawPathNode->clear();
		for (int i=0; i<1; ++i) {
			drawPath(Vec2(10,10), Vec2(900,600));
		}
	}
}

Graph* TileMap::getGraph() {

	Graph *g = new Graph(tileI * tileJ);

	for (int i=0; i<tileI; ++i) {
		for (int j=0; j<tileJ; ++j) {
			// ����8�������ϵ����ӣ�˳ʱ�봦��
			/*************************************
			���Ϸ�    �Ϸ�     ���Ϸ�

			��	   *         �ҷ�

			���·�	  �·�     ���·�
			**************************************/

			// �Ϸ�
			if (i+1 < tileI) {
				if (matrix[i+1][j] < 1E6) {
					g->insertArc(i*tileJ+j, (i+1)*tileJ+j, matrix[i+1][j]);
				}
			}

			// ���Ϸ�
			if (i+1 < tileI && 
				j+1 < tileJ) {
					if (matrix[i+1][j+1] < 1E6) {
						g->insertArc(i*tileJ+j, (i+1)*tileJ+j+1, matrix[i+1][j+1]*1.414f);
					}
			}

			// �ҷ�
			if (j+1 < tileJ) {
				if (matrix[i][j+1] < 1E6) {
					g->insertArc(i*tileJ+j, (i)*tileJ+j+1, matrix[i][j+1]);
				}
			}

			// ���·�
			if (i-1 > 0 &&
				j+1 < tileJ) {
					if (matrix[i-1][j+1] < 1E6) {
						g->insertArc(i*tileJ+j, (i-1)*tileJ+j+1, matrix[i-1][j+1]*1.414f);
					}
			}

			// �·�
			if (i-1 > 0) {
				if (matrix[i-1][j] < 1E6) {
					g->insertArc(i*tileJ+j, (i-1)*tileJ+j, matrix[i-1][j]);
				}
			}

			// ���·�
			if (i-1 > 0 &&
				j-1 > 0) {
					if (matrix[i-1][j-1] < 1E6) {
						g->insertArc(i*tileJ+j, (i-1)*tileJ+j-1, matrix[i-1][j-1]*1.414f);
					}
			}

			// ��
			if (i-1 > 0) {
				if (matrix[i-1][j] < 1E6) {
					g->insertArc(i*tileJ+j, (i-1)*tileJ+j, matrix[i-1][j]);
				}
			}

			// ���Ϸ�
			if (i+1 < tileI &&
				j-1 > 0) {
					if (matrix[i+1][j-1] < 1E6) {
						g->insertArc(i*tileJ+j, (i+1)*tileJ+j-1, matrix[i+1][j-1]*1.414f);
					}
			}
		}
	}
	return g;
}



void TileMap::print() {
	printf("\n");
	for (int i=0; i<tileI; ++i) {
		for (int j=0; j<tileJ; ++j) {
			printf("[%d][%d]%f ", i,j, matrix[i][j]);
		}
		printf("\n\n");
	}
}

void TileMap::printObstacle() {
	printf("\n");
	for (int i=0; i<tileI; ++i) {
		for (int j=0; j<tileJ; ++j) {
			if (matrix[i][j] > 1E6) {
				printf("[%d][%d]%f ", i,j, matrix[i][j]);
			}
		}
		printf("\n\n");
	}
}