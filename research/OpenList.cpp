/**************************************************************
* ���ߣ���ε
* ���£�2014-07-15
***************************************************************/

#include "OpenList.h"

/***************************************************************
*             ���캯������������                               *
****************************************************************/
OpenList::OpenList(int cap) : 
	_size(0), 
	_value(new float[cap]),
	_v2n_index(new int[cap]),
	_n2v_index(new int[cap]) {
	for (int i=0; i<cap; ++i) {
		_value[i]     = 1E7;
		_v2n_index[i] = -1;
		_n2v_index[i] = -1;
	}
}

OpenList::~OpenList() {
	if (_value != nullptr) { 
		delete[] _value;
	}
	if (_v2n_index != nullptr) {
		delete[] _v2n_index;
	}
	if (_n2v_index != nullptr) {
		delete[] _n2v_index;
	}
}

/***************************************************************
*             OpenList�� �� ɾ ��(Ҳ��insert)                  *
****************************************************************/
void OpenList::insert(int index, float cost) {
	if (isContain(index)) {
		// �ظ�����ʱ�����Ƿ��Ѿ����ڣ����������ֵ��������
		auto i = _n2v_index[index];
		if (cost < _value[i]) {
			_value[i] = cost;
			_siftUp(i);
			_siftDown(i);
		}
	} else {
		_v2n_index[_size] = index;
		_n2v_index[index] = _size;
		_value[_size] = cost;
		_siftUp(_size);
		++_size;
	}
}

bool OpenList::extractMin(int &index, float &cost) {
	index = _v2n_index[0];
	cost  = _value[0];
	std::swap(_v2n_index[0], _v2n_index[_size-1]);
	std::swap(_value[0], _value[_size-1]);
	--_size;
	_siftDown(0);
	_n2v_index[index] = -1;
	return true;
}
	
/***************************************************************
*             OpenList��Ԫ�ذ����ж���Ԫ������                 *
****************************************************************/
bool OpenList::isContain(int index) {
	return _n2v_index[index] != -1;
}

bool OpenList::isEmpty() {
	return _size <= 0;
}

inline int OpenList::getSize() {
	return _size;
}

/***************************************************************
*             OpenList����ά���ڲ��ṹ�ĶѲ���                 *
****************************************************************/
void OpenList::_siftUp(int end) {
	// ��ӵ�Ԫ����ĩβ
	uint32_t cur = end;
	// ÿ�εĲ��� _value _v2n_index _n2v_index��������ͬ����
	auto tmp_value = _value[cur];
	auto tmp_v2n_index = _v2n_index[cur];
	auto tmp_n2v_index = _n2v_index[_v2n_index[cur]];

	while (cur!=0 && tmp_value < _value[(cur-1)>>1]) {
		// ÿ�εĲ��� _value _v2n_index _n2v_index��������ͬ����
		_value[cur] = _value[(cur-1)>>1];
		_v2n_index[cur] = _v2n_index[(cur-1)>>1];
		_n2v_index[_v2n_index[(cur-1)>>1]] = cur;
		cur = (cur-1)>>1;
	}
	// ÿ�εĲ��� _value _v2n_index _n2v_index��������ͬ����
	_value[cur] = tmp_value;
	_v2n_index[cur] = tmp_v2n_index;
	_n2v_index[tmp_v2n_index] = cur;
}

void OpenList::_siftDown(int begin) {
	uint32_t cur = begin;
	// ÿ�εĲ��� _value _v2n_index _n2v_index��������ͬ����
	auto tmp_value = _value[cur];
	auto tmp_v2n_index = _v2n_index[cur];
	auto tmp_n2v_index = _n2v_index[_v2n_index[cur]];

	// ����������
	while ((cur<<1)+1 < _size) {
		// nextָ�����Һ����и�С��һ��
		uint32_t next = (cur<<1)+1; 
		if (next+1<_size && _value[next+1]<_value[next]) {
			++next; 
		} 
		// �������С�ĺ��Ӹ���
		if (_value[next] < tmp_value) { 
			// ÿ�εĲ��� _value _v2n_index _n2v_index��������ͬ����
			_value[cur] = _value[next];
			_v2n_index[cur] = _v2n_index[next];
			_n2v_index[_v2n_index[next]] = cur;
			cur = next;
		} else {
		// ���Ⱥ��Ӹ���
			break;
		}
	}
	// ÿ�εĲ��� _value _v2n_index _n2v_index��������ͬ����
	_value[cur] = tmp_value;
	_v2n_index[cur] = tmp_v2n_index;
	_n2v_index[tmp_v2n_index] = cur;
}