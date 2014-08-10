#include <stdint.h>


//��ά��״����
template <typename T>
class TreeArray2 {
public:
	static inline int lowbit(int x) {
		return x&(-x);
	}
public:
	TreeArray2(T** arr, int sizeI, int sizeJ) {
		// ��ʼ����ά���󣬶��ʼ��һ�� һ��
		treeArray = new T*[sizeI+1];
		for (int i=0; i<=sizeI; ++i) {
			treeArray[i] = new T[sizeJ+1];//0��Ԫ�ر���
			for (int j=0; j<=sizeJ; ++j) {
				treeArray[i][j] = 0;
			}
		}
		treeSizeI = sizeI;
		treeSizeJ = sizeJ;
		// ���뽨����״����
		for (int i=0; i<sizeI; ++i) {
			for (int j=0; j<sizeJ; ++j) {
				update(i, j, arr[i][j]);
			}
		}
	}

	~TreeArray2() {
		if (treeArray != nullptr) {
			delete[] treeArray;
		}
	}

	int getSum(int i, int j)  {
		T sum = 0;
		for (int _i=i+1; _i>0; _i-=lowbit(_i)) {
			for (int _j=j+1; _j>0; _j-=lowbit(_j)) {
				sum += treeArray[_i][_j];
			}
		}
		return sum;
	}

	void update(int i, int j, int delta) {
		for (int _i=i+1; _i<=treeSizeI; _i+=lowbit(_i)) {
			for (int _j=j+1; _j<=treeSizeJ; _j+=lowbit(_j)) {
				treeArray[_i][_j] += delta;
			}
		}
	}

	T** treeArray;
	int treeSizeI;
	int treeSizeJ;
};




//һά��״����
template <typename T>
class TreeArray1 {
public:
	static inline int lowbit(int x) {
		return x&(-x);
	}
public:
	TreeArray1(T* arr, int size) {
		//����һ�ݵ�����
		treeArray = new T[size+1];       //0��Ԫ�ر���
		for (int i=1; i<=size; ++i) {
			treeArray[i] = arr[i-1];
		}
		//������״����
		int step = 2;
		while (step < size) {
			for (int i=step; i<=size; i+=step) {
				treeArray[i] = treeArray[i] + treeArray[i-(step>>1)];
			}
			step += step;
		}
		treeSize = size;
	}
	~TreeArray1() {
		if (treeArray != nullptr) {
			delete[] treeArray;
		}
	}

	T getSum(int i)  {
		int _i = i+1;
		T sum = 0;
		while (_i>0) {
			sum += treeArray[_i];
			_i -= lowbit(_i);
		}
		return sum;
	}

	void update(int i, T delta) {
		int _i = i+1;
		while (_i<=treeSize) {
			treeArray[_i] += delta;
			_i += lowbit(_i);
		}
	}

	T*     treeArray;
	int treeSize;
};

//֧��������µĶ�ά��״����
template <typename T>
class TreeArray {
public:

public:
	TreeArray(T** arr, int sizeI, int sizeJ) {
		treeArray = new TreeArray2<T>(arr, sizeI, sizeJ);
	}

	~TreeArray() {
		if (treeArray != nullptr) {
			delete treeArray;
		}
	}

	// �ݳ�ԭ��
	T getSum(int i1, int j1,
			   int i2, int j2)  {
		return treeArray->getSum(i2, j2)   -
			   treeArray->getSum(i2, j1-1) -
			   treeArray->getSum(i1-1, j2) +
			   treeArray->getSum(i1-1, j1-1);
	}

	void update(int i1, int j1,
				int i2, int j2,
				int delta) {
		for (int i=i1; i<=i2; ++i) {
			for (int j=j1; j<=j2; ++j) {
				treeArray->update(i, j, delta);
			}
		}
	}

	TreeArray2<T> *treeArray;
};
