/***************************************************
*  作者：汪蔚                                      *
*  更新：2014-07-17                                *
****************************************************/
#ifndef __TILE_MAP_H__
#define __TILE_MAP_H__
#include "cocos2d.h"
#include "Graph.h"
#include "GCPhysicsWorld.h"


const static float GRID_SCALE = 1.0f/10.0f;  //横坐标的1/10

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

	// 坐标变换
	ScreenCoord getScreenCoord(TileCoord tileCoord);
	ScreenCoord getScreenCoord(GraphCoord graphCoord);
	GraphCoord getGraphCoord(TileCoord tileCoord);
	GraphCoord getGraphCoord(ScreenCoord screenCoord);
	TileCoord getTileCoord(GraphCoord graphCoord);
	TileCoord getTileCoord(ScreenCoord screenCoord);
	
	
	
	float **matrix;      // 每个节点记录要经过这个节点的代价
	float contentWidth;  // 区域宽度
	float contentHeight; // 区域高度
	int tileJ;           // 地图的X轴长度,数组的j
	int tileI;           // 地图的Y轴长度,数组的i


	cocos2d::DrawNode *drawAsterNode;
	cocos2d::DrawNode *drawGridNode;
	cocos2d::DrawNode *drawPathNode;
};

Graph* tileToGraph(TileMap *tileMap);

#endif