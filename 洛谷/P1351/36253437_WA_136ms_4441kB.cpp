#include <bits/stdc++.h>
using namespace std;
const int maxn = 200010;
int n, a[maxn], b[maxn], w[maxn];
void link(int x, int y) {
	if (a[x]) b[x] = y;
	else a[x] = y;
}
int main() {
	scanf("%d", &n);
	int x, y;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		link(x, y), link(y, x);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	int sum = 0, maxx = 0;
	for (int i = 1; i <= n; i++) {
		maxx = max(maxx, w[a[i]] * w[b[i]]);
		sum = (sum + w[a[i]] * w[b[i]]) % 10007;
	}
	printf("%d %d", maxx, (sum * 2) % 10007);
} 