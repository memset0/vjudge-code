#include <bits/stdc++.h> 
using namespace std;
const int maxn = 100010;
int n, a[maxn];
void qsort(int left, int right) {
	if (left >= right) return ;
	int key = a[left], i = left, j = right;
	while (i < j) {
		while (i < j && a[j] >= key) j--;
		a[i] = a[j];
		while (i < j && a[i] <= key) i++;
		a[j] = a[i];
//	printf("%d %d %d %d %d\n", key, left, right, i, j);
	}
	a[i] = key;
	qsort(left, i - 1);
	qsort(i + 1, right);
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	qsort(1, n);
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	return 0;
}