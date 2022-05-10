#include <bits/stdc++.h>
#define il inline
using namespace std;

int mrk; char chr;
il void _R(int &x) {
	x = 0, chr = getchar(), mrk = 1;
	while (!('0' <= chr && chr <= '9') && chr != '-') chr = getchar();
	if (chr == '-') mrk = -1, chr = getchar();
	while ('0' <= chr && chr <= '9') x = x * 10 + chr - '0', chr = getchar();
	x *= mrk;
}

const int maxn = 100010;
int n, ans, a[maxn], f[maxn], g[maxn];
int i, j;

int main() {
//	freopen("flower.in", "r", stdin);
//	freopen("flower.out", "w", stdout);
	_R(n);
	for (i = 1; i <= n; ++i) _R(a[i]);
	for (i = 1; i <= n; ++i) {
		f[i] = 1;
		for (j = 1; j < i; ++j)	
			if (f[j] % 2 && a[i] > a[j]) f[i] = max(f[i], f[j] + 1);
			else if (!(f[j] % 2) && a[i] < a[j]) f[i] = max(f[i], f[j] + 1);
		ans = max(ans, f[i]);
	}
//	for (i = 1; i <= n; ++i)
//		cout << f[i] << " " ;
//	cout << endl;
	for (i = 1; i <= n; ++i) {
		g[i] = 1;
		for (j = 1; j < i; ++j)	
			if (g[j] % 2 && a[i] < a[j]) g[i] = max(g[i], g[j] + 1);
			else if (!(g[j] % 2) && a[i] > a[j]) g[i] = max(g[i], g[j] + 1);
		ans = max(ans, g[i]);
	}
//	for (i = 1; i <= n; ++i)
//		cout << g[i] << " " ;
//	cout << endl;
	printf("%d\n", ans);
	return 0;
}