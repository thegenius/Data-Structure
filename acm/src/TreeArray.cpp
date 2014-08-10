#include "TreeArry.h"




int _tmain(int argc, _TCHAR* argv[]) {
	int arr_tmp[10] = {1,2,3,4,5,6,7,8,9,10};
	TreeArray1<int>arr(arr_tmp, 10);

	arr.update(2, 1);
	for (int i=0; i<10; ++i) {
		printf("%d\n", arr.getSum(i));
	}
	
	int sizeI = 4;
	int sizeJ = 5;
	float **arr_tmp2 = new float*[sizeI];
	for (int i=0; i<sizeI; ++i) {
		arr_tmp2[i] = new float[sizeJ]; //0ºÅÔªËØ±£Áô
		for (int j=0; j<sizeJ; ++j) {
			arr_tmp2[i][j] = i*sizeJ+j;
			printf("[%d][%d]%d ",i,j,arr_tmp2[i][j]);
		}
		printf("\n");
	}
	puts("");



	TreeArray2<float> arr2(arr_tmp2, sizeI, sizeJ);
	for (int i=0; i<sizeI; ++i) {
		for (int j=0; j<sizeJ; ++j) {
			printf("[%d][%d]%d ", i,j, arr2.getSum(i,j));
		}
		printf("\n");
	}
	puts("");
	
	TreeArray<float> arr3(arr_tmp2, sizeI, sizeJ);
	for (int i=0; i<sizeI; ++i) {
		for (int j=0; j<sizeJ; ++j) {
			printf("[%d][%d]%f ", i,j, arr3.getSum(i,j, i, j));
		}
		printf("\n");
	}
	printf("%f\n", arr3.getSum(0,0, sizeI-1, sizeJ-1));

	getchar();

	return 0;
}

