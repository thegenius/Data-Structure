#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
    
    freopen("d:\\c\\in.txt","r",stdin);
    freopen("d:\\c\\out.txt","w",stdout);
    printf("hello world");
    int arr[10];
    int n;
    scanf("%d\n",&n);
    for(int i=0; i<n; ++i)
	scanf("%d",&arr[i]);
    sort(arr,arr+n);
    for(int i=0; i<n; ++i)
	printf("%d\t",arr[i]);

    printf("\n");
    fclose(stdin);
    fclose(stdout);
    return 0;
}
