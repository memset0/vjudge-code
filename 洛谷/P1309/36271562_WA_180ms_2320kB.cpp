#include <bits/stdc++.h> 
using namespace std;
const int maxn = 100010;
int n, m, q;
struct S{
	int i, w, k;
} a[2 * maxn];
bool my_sort(S a, S b) {
	if (a.w == b.w) return a.i < b.i;
	return a.w > b.w;
}
int main() {
	cin >> n >> m >> q;
	for (int i = 1; i <= 2 * n; i++)
		a[i].i = i;
	for (int i = 1; i <= 2 * n; i++)
		scanf("%d", &a[i].w);
	for (int i = 1; i <= 2 * n; i++)
		scanf("%d", &a[i].k);
	for (int i = 1; i <= m; i++) {
		sort(a + 1, a + 2 * n + 1, my_sort);
		for (int i = 1; i <= n; i += 2)
			if (a[i].k > a[i + 1].k) a[i].w += 1;
			else a[i + 1].w += 1;
	}
	cout << a[q].i << endl;
	return 0;
}