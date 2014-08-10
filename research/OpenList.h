/**********************************************************************************
*         OpenList的特性使其可以用于Dijkstra、A star等路径搜索算法                *
*         因为各种路径搜索算法中都可以使用这种辅助结构，所以单独抽取出来          *
*         目前的实现是基于二叉堆的，后续可以改进为更加高级的堆结构                *
*         作者：汪蔚 2014-07-15                                                   *
***********************************************************************************/

#ifndef __OPEN_LIST_H__
#define __OPEN_LIST_H__
#include <stdint.h>
#include <algorithm>



/**********************************************
*     定义部分，注意insert同时具有更新功能    *
*     对外显示提供的操作只有：                *
*    （1）插入更新元素   insert               *
*    （2）提取最小元素   extractMin           *
*    （3）查询是否包含   isContain            *
*    （4）查询当前容量   getSize              *
*    （5）查询是否为空   isEmpty              *
***********************************************/
class OpenList {
public:
	OpenList(int cap);                        //内部并不保留capacity,因为这类算法初始化时一般都知道所需要的最大空间
	~OpenList();

	void insert(int index, float cost);         // 添加元素，如果是重复元素，检查cost大小，如果更小就更新
	bool extractMin(int &index, float &cost);   // 获取最小元素，并在堆中删除
	bool isContain(int index);                // 查询是否包含
	bool isEmpty();                           
	int  getSize();

private:
	void _siftUp(int end);
	void _siftDown(int begin);

private:
	uint32_t _size;             // 已经插入的元素的个数
	float *_value;                // value 值作为堆操作的基础
	int *_v2n_index;            // value值   映射到 node  的外部编号
	int *_n2v_index;            // node编号  映射到 value 在堆中的位置下标
};

#endif