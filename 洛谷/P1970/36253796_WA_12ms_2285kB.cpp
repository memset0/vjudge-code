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
	int sum = 0;
	for (i = 2; i <= n; ++i)
		if (a[i] > a[i - 1]) sum++;
		else if (a[i] < a[i - 1]) sum--;
	ans = n - abs(sum);
	printf("%d\n", ans);
	return 0;
}