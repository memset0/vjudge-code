#include <bits/stdc++.h>
using namespace std;
template <typename T> void chkmax(T &x, T y) {x = x > y ? x : y;}
template <typename T> void chkmin(T &x, T y) {x = x > y ? y : x;}
template <typename T> void read(T &x) {
	x = 0; int f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar(); x *= f;
}
const int N = 2010, mod = 1e6;
int l, a[N], b[N], d[N];
void divide(int x, int v, int m) {
	for (int i = 2; i * i <= x; i++)
		while (x % i == 0) a[i] += v * m, x /= i;
	if (x > 1) a[x] += v * m;
}
void mul(int x) {
	for (int i = 1; i <= l; i++) b[i] *= x;
	for (int i = 1; i <= l; i++)
		b[i + 1] += b[i] / mod, b[i] %= mod;
	while (b[l + 1] > 0) l++, b[l + 1] += b[l] / mod, b[l] %= mod;
}
int main() {
	int n; read(n); int len = n - 2, m = 0;
	for (int i = 1; i <= n; i++) {
		read(d[i]); if (!d[i]) return cout << "0\n", 0;
		if (~d[i]) d[i]--, len -= d[i]; else m++;
	}
	if (len < 0) return cout << "0\n", 0; b[l = 1] = 1;
	for (int i = 1; i <= n - 2; i++) divide(i, 1, 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= d[i]; j++)
			divide(j, -1, 1);
	for (int i = 1; i <= len; i++) divide(i, -1, 1), mul(m);
	for (int i = 1; i <= n; i++) while (a[i]--) mul(i);
	for (int i = l; i; i--)
		if (i == l) printf("%d", b[i]); else printf("%06d", b[i]);
	puts("");
	return 0;
}