/***************************************************
*  ���ߣ���ε                                      *
*  ���£�2014-07-17                                *
****************************************************/
#ifndef __TILE_MAP_H__
#define __TILE_MAP_H__
#include "cocos2d.h"
#include "Graph.h"
#include "GCPhysicsWorld.h"


const static float GRID_SCALE = 1.0f/10.0f;  //�������1/10

struct TileCoord { 
	TileCoord(int i=0, int j=0) : i(i), j(j) {
	};
	int i; 
	int j;
};
typedef int GraphCoord;
typedef cocos2d::Vec2 ScreenCoord;

struct TileMap : public cocos2d::Node{
public:
	TileMap(float width=960.0f, float height=600.0f);
	static TileMap* create(float width=960.0f, float height=600.0f);
	virtual bool init();
	Graph* getGraph();
	bool   makeTileMapFromPhysics();

	void   drawGrid();
	void   drawAsterByTile();
	void   drawAsterByGraph();
	void   drawPath(cocos2d::Vec2 src, cocos2d::Vec2 dst);

	void   print();
	void   printObstacle();

	void   update(float dt);

	// ����任
	ScreenCoord getScreenCoord(TileCoord tileCoord);
	ScreenCoord getScreenCoord(GraphCoord graphCoord);
	GraphCoord getGraphCoord(TileCoord tileCoord);
	GraphCoord getGraphCoord(ScreenCoord screenCoord);
	TileCoord getTileCoord(GraphCoord graphCoord);
	TileCoord getTileCoord(ScreenCoord screenCoord);
	
	
	
	float **matrix;      // ÿ���ڵ��¼Ҫ��������ڵ�Ĵ���
	float contentWidth;  // ������
	float contentHeight; // ����߶�
	int tileJ;           // ��ͼ��X�᳤��,�����j
	int tileI;           // ��ͼ��Y�᳤��,�����i


	cocos2d::DrawNode *drawAsterNode;
	cocos2d::DrawNode *drawGridNode;
	cocos2d::DrawNode *drawPathNode;
};

Graph* tileToGraph(TileMap *tileMap);

#endif