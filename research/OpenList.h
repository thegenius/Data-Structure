/**********************************************************************************
*         OpenList������ʹ���������Dijkstra��A star��·�������㷨                *
*         ��Ϊ����·�������㷨�ж�����ʹ�����ָ����ṹ�����Ե�����ȡ����          *
*         Ŀǰ��ʵ���ǻ��ڶ���ѵģ��������ԸĽ�Ϊ���Ӹ߼��Ķѽṹ                *
*         ���ߣ���ε 2014-07-15                                                   *
***********************************************************************************/

#ifndef __OPEN_LIST_H__
#define __OPEN_LIST_H__
#include <stdint.h>
#include <algorithm>



/**********************************************
*     ���岿�֣�ע��insertͬʱ���и��¹���    *
*     ������ʾ�ṩ�Ĳ���ֻ�У�                *
*    ��1���������Ԫ��   insert               *
*    ��2����ȡ��СԪ��   extractMin           *
*    ��3����ѯ�Ƿ����   isContain            *
*    ��4����ѯ��ǰ����   getSize              *
*    ��5����ѯ�Ƿ�Ϊ��   isEmpty              *
***********************************************/
class OpenList {
public:
	OpenList(int cap);                        //�ڲ���������capacity,��Ϊ�����㷨��ʼ��ʱһ�㶼֪������Ҫ�����ռ�
	~OpenList();

	void insert(int index, float cost);         // ���Ԫ�أ�������ظ�Ԫ�أ����cost��С�������С�͸���
	bool extractMin(int &index, float &cost);   // ��ȡ��СԪ�أ����ڶ���ɾ��
	bool isContain(int index);                // ��ѯ�Ƿ����
	bool isEmpty();                           
	int  getSize();

private:
	void _siftUp(int end);
	void _siftDown(int begin);

private:
	uint32_t _size;             // �Ѿ������Ԫ�صĸ���
	float *_value;                // value ֵ��Ϊ�Ѳ����Ļ���
	int *_v2n_index;            // valueֵ   ӳ�䵽 node  ���ⲿ���
	int *_n2v_index;            // node���  ӳ�䵽 value �ڶ��е�λ���±�
};

#endif