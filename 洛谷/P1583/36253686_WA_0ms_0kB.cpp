#include <bits/stdc++.h> 
using namespace std;
const int maxn = 20010;
int n, m, e[maxn], w[maxn], c[maxn], d[maxn], k[maxn];
bool my_sort(int a, int b) {
	return w[a] > w[b];
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		scanf("%d", &e[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for (int i = 1; i <= n; i++)
		d[i] = i, k[i] = i;
	sort(d + 1, d + n + 1, my_sort);
	for (int i = 1; i <= n; i++) {
		c[i] = (d[i] - 1) % 10 + 1;
		w[i] += e[c[i]];
	}
	sort(k + 1, k + n + 1, my_sort);
	for (int i = 1; i <= n; i++) {
		printf("%d ", k[i]);
	}
	return 0;
}