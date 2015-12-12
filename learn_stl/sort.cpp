#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

int cmp(const void *a, const void *b){
	return *(int *)a - *(int *)b ;
}
void _qsort(int *a, int l, int r) {
	if(l >= r) return;
	int first = l, last = r;
	int key = a[first];
	while(first < last) {
		while( last > first && a[last] >= key) last--;
		a[first] = a[last];
		while( first < last  && a[first] <= key) first++;
		a[last] = a[first];
	}
	a[first] = key;
	_qsort(a, l, first - 1);
	_qsort(a, first + 1, r);
}
int main() {
	const int n = 60000;
	int a[n];
	for( int i = 0; i < n; i++)
		a[i] = n - i;
	_qsort(a, 0, n - 1);
	//sort(a, a + n);
	//qsort(a, n, sizeof(int), cmp);
	cout<<"finish"<<endl;
}
